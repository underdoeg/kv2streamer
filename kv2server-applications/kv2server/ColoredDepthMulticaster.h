/*
 * Copyright (c) 2014 Samsung Electronics Corporation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "AbstractMulticaster.h"
#include <gst-wrapper/GstAppSrcPipeline.h>

class ColoredDepthMulticaster : public AbstractMulticaster
{
public:
	ColoredDepthMulticaster(std::string multicastIP, int port);
	~ColoredDepthMulticaster(void);

	virtual HRESULT InitializeMulticasterAndSubscribeHandle(IKinectSensor* kinectSensor, WAITABLE_HANDLE &waitableHandle);
	virtual void ProcessNewFrame(WAITABLE_HANDLE &waitableHandle);

private:

	IMultiSourceFrameReader*	multiFrameReader;
	ICoordinateMapper*			coordinateMapper;

	kv2s::GstAppSrcPipeline		gstSender;
	
	RGBQUAD						default_black; 

	void						ProcessNewColorAndDepthFrame(IColorFrame* colorFrame, IDepthFrame* depthFrame);
	void						ComposeOutputColoredDepthBuffer(UINT16* depthBuffer, USHORT maxReliableDistance, USHORT minReliableDist);

	ColorSpacePoint*			pColorSpacePoints;
	RGBQUAD*					pInputFullRGBX;
	RGBQUAD*					pOutputColoredDepth;						
};

