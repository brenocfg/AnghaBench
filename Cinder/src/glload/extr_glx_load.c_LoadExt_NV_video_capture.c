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
typedef  scalar_t__ PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC ;
typedef  scalar_t__ PFNGLXBINDVIDEOCAPTUREDEVICENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXBindVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_glXEnumerateVideoCaptureDevicesNV ; 
 scalar_t__ _funcptr_glXLockVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_glXQueryVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_glXReleaseVideoCaptureDeviceNV ; 

__attribute__((used)) static int LoadExt_NV_video_capture()
{
	int numFailed = 0;
	_funcptr_glXBindVideoCaptureDeviceNV = (PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("glXBindVideoCaptureDeviceNV");
	if(!_funcptr_glXBindVideoCaptureDeviceNV) ++numFailed;
	_funcptr_glXEnumerateVideoCaptureDevicesNV = (PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)IntGetProcAddress("glXEnumerateVideoCaptureDevicesNV");
	if(!_funcptr_glXEnumerateVideoCaptureDevicesNV) ++numFailed;
	_funcptr_glXLockVideoCaptureDeviceNV = (PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("glXLockVideoCaptureDeviceNV");
	if(!_funcptr_glXLockVideoCaptureDeviceNV) ++numFailed;
	_funcptr_glXQueryVideoCaptureDeviceNV = (PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("glXQueryVideoCaptureDeviceNV");
	if(!_funcptr_glXQueryVideoCaptureDeviceNV) ++numFailed;
	_funcptr_glXReleaseVideoCaptureDeviceNV = (PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("glXReleaseVideoCaptureDeviceNV");
	if(!_funcptr_glXReleaseVideoCaptureDeviceNV) ++numFailed;
	return numFailed;
}