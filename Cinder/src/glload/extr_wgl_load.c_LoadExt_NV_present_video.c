#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ PFNWGLQUERYCURRENTCONTEXTNVPROC ;
typedef  scalar_t__ PFNWGLENUMERATEVIDEODEVICESNVPROC ;
typedef  scalar_t__ PFNWGLBINDVIDEODEVICENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglBindVideoDeviceNV ; 
 scalar_t__ _funcptr_wglEnumerateVideoDevicesNV ; 
 scalar_t__ _funcptr_wglQueryCurrentContextNV ; 

__attribute__((used)) static int LoadExt_NV_present_video()
{
	int numFailed = 0;
	_funcptr_wglBindVideoDeviceNV = (PFNWGLBINDVIDEODEVICENVPROC)IntGetProcAddress("wglBindVideoDeviceNV");
	if(!_funcptr_wglBindVideoDeviceNV) ++numFailed;
	_funcptr_wglEnumerateVideoDevicesNV = (PFNWGLENUMERATEVIDEODEVICESNVPROC)IntGetProcAddress("wglEnumerateVideoDevicesNV");
	if(!_funcptr_wglEnumerateVideoDevicesNV) ++numFailed;
	_funcptr_wglQueryCurrentContextNV = (PFNWGLQUERYCURRENTCONTEXTNVPROC)IntGetProcAddress("wglQueryCurrentContextNV");
	if(!_funcptr_wglQueryCurrentContextNV) ++numFailed;
	return numFailed;
}