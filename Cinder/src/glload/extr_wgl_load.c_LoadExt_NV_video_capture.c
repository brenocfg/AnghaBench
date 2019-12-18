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
typedef  scalar_t__ PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC ;
typedef  scalar_t__ PFNWGLBINDVIDEOCAPTUREDEVICENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglBindVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_wglEnumerateVideoCaptureDevicesNV ; 
 scalar_t__ _funcptr_wglLockVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_wglQueryVideoCaptureDeviceNV ; 
 scalar_t__ _funcptr_wglReleaseVideoCaptureDeviceNV ; 

__attribute__((used)) static int LoadExt_NV_video_capture()
{
	int numFailed = 0;
	_funcptr_wglBindVideoCaptureDeviceNV = (PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("wglBindVideoCaptureDeviceNV");
	if(!_funcptr_wglBindVideoCaptureDeviceNV) ++numFailed;
	_funcptr_wglEnumerateVideoCaptureDevicesNV = (PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)IntGetProcAddress("wglEnumerateVideoCaptureDevicesNV");
	if(!_funcptr_wglEnumerateVideoCaptureDevicesNV) ++numFailed;
	_funcptr_wglLockVideoCaptureDeviceNV = (PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("wglLockVideoCaptureDeviceNV");
	if(!_funcptr_wglLockVideoCaptureDeviceNV) ++numFailed;
	_funcptr_wglQueryVideoCaptureDeviceNV = (PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("wglQueryVideoCaptureDeviceNV");
	if(!_funcptr_wglQueryVideoCaptureDeviceNV) ++numFailed;
	_funcptr_wglReleaseVideoCaptureDeviceNV = (PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)IntGetProcAddress("wglReleaseVideoCaptureDeviceNV");
	if(!_funcptr_wglReleaseVideoCaptureDeviceNV) ++numFailed;
	return numFailed;
}