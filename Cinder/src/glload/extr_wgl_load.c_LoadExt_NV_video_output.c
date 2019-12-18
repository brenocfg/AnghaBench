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
typedef  scalar_t__ PFNWGLSENDPBUFFERTOVIDEONVPROC ;
typedef  scalar_t__ PFNWGLRELEASEVIDEOIMAGENVPROC ;
typedef  scalar_t__ PFNWGLRELEASEVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNWGLGETVIDEOINFONVPROC ;
typedef  scalar_t__ PFNWGLGETVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNWGLBINDVIDEOIMAGENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglBindVideoImageNV ; 
 scalar_t__ _funcptr_wglGetVideoDeviceNV ; 
 scalar_t__ _funcptr_wglGetVideoInfoNV ; 
 scalar_t__ _funcptr_wglReleaseVideoDeviceNV ; 
 scalar_t__ _funcptr_wglReleaseVideoImageNV ; 
 scalar_t__ _funcptr_wglSendPbufferToVideoNV ; 

__attribute__((used)) static int LoadExt_NV_video_output()
{
	int numFailed = 0;
	_funcptr_wglBindVideoImageNV = (PFNWGLBINDVIDEOIMAGENVPROC)IntGetProcAddress("wglBindVideoImageNV");
	if(!_funcptr_wglBindVideoImageNV) ++numFailed;
	_funcptr_wglGetVideoDeviceNV = (PFNWGLGETVIDEODEVICENVPROC)IntGetProcAddress("wglGetVideoDeviceNV");
	if(!_funcptr_wglGetVideoDeviceNV) ++numFailed;
	_funcptr_wglGetVideoInfoNV = (PFNWGLGETVIDEOINFONVPROC)IntGetProcAddress("wglGetVideoInfoNV");
	if(!_funcptr_wglGetVideoInfoNV) ++numFailed;
	_funcptr_wglReleaseVideoDeviceNV = (PFNWGLRELEASEVIDEODEVICENVPROC)IntGetProcAddress("wglReleaseVideoDeviceNV");
	if(!_funcptr_wglReleaseVideoDeviceNV) ++numFailed;
	_funcptr_wglReleaseVideoImageNV = (PFNWGLRELEASEVIDEOIMAGENVPROC)IntGetProcAddress("wglReleaseVideoImageNV");
	if(!_funcptr_wglReleaseVideoImageNV) ++numFailed;
	_funcptr_wglSendPbufferToVideoNV = (PFNWGLSENDPBUFFERTOVIDEONVPROC)IntGetProcAddress("wglSendPbufferToVideoNV");
	if(!_funcptr_wglSendPbufferToVideoNV) ++numFailed;
	return numFailed;
}