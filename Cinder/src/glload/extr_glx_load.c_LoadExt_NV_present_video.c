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
typedef  scalar_t__ PFNGLXENUMERATEVIDEODEVICESNVPROC ;
typedef  scalar_t__ PFNGLXBINDVIDEODEVICENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXBindVideoDeviceNV ; 
 scalar_t__ _funcptr_glXEnumerateVideoDevicesNV ; 

__attribute__((used)) static int LoadExt_NV_present_video()
{
	int numFailed = 0;
	_funcptr_glXBindVideoDeviceNV = (PFNGLXBINDVIDEODEVICENVPROC)IntGetProcAddress("glXBindVideoDeviceNV");
	if(!_funcptr_glXBindVideoDeviceNV) ++numFailed;
	_funcptr_glXEnumerateVideoDevicesNV = (PFNGLXENUMERATEVIDEODEVICESNVPROC)IntGetProcAddress("glXEnumerateVideoDevicesNV");
	if(!_funcptr_glXEnumerateVideoDevicesNV) ++numFailed;
	return numFailed;
}