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
typedef  scalar_t__ PFNGLXSENDPBUFFERTOVIDEONVPROC ;
typedef  scalar_t__ PFNGLXRELEASEVIDEOIMAGENVPROC ;
typedef  scalar_t__ PFNGLXRELEASEVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNGLXGETVIDEOINFONVPROC ;
typedef  scalar_t__ PFNGLXGETVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNGLXBINDVIDEOIMAGENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXBindVideoImageNV ; 
 scalar_t__ _funcptr_glXGetVideoDeviceNV ; 
 scalar_t__ _funcptr_glXGetVideoInfoNV ; 
 scalar_t__ _funcptr_glXReleaseVideoDeviceNV ; 
 scalar_t__ _funcptr_glXReleaseVideoImageNV ; 
 scalar_t__ _funcptr_glXSendPbufferToVideoNV ; 

__attribute__((used)) static int LoadExt_NV_video_output()
{
	int numFailed = 0;
	_funcptr_glXBindVideoImageNV = (PFNGLXBINDVIDEOIMAGENVPROC)IntGetProcAddress("glXBindVideoImageNV");
	if(!_funcptr_glXBindVideoImageNV) ++numFailed;
	_funcptr_glXGetVideoDeviceNV = (PFNGLXGETVIDEODEVICENVPROC)IntGetProcAddress("glXGetVideoDeviceNV");
	if(!_funcptr_glXGetVideoDeviceNV) ++numFailed;
	_funcptr_glXGetVideoInfoNV = (PFNGLXGETVIDEOINFONVPROC)IntGetProcAddress("glXGetVideoInfoNV");
	if(!_funcptr_glXGetVideoInfoNV) ++numFailed;
	_funcptr_glXReleaseVideoDeviceNV = (PFNGLXRELEASEVIDEODEVICENVPROC)IntGetProcAddress("glXReleaseVideoDeviceNV");
	if(!_funcptr_glXReleaseVideoDeviceNV) ++numFailed;
	_funcptr_glXReleaseVideoImageNV = (PFNGLXRELEASEVIDEOIMAGENVPROC)IntGetProcAddress("glXReleaseVideoImageNV");
	if(!_funcptr_glXReleaseVideoImageNV) ++numFailed;
	_funcptr_glXSendPbufferToVideoNV = (PFNGLXSENDPBUFFERTOVIDEONVPROC)IntGetProcAddress("glXSendPbufferToVideoNV");
	if(!_funcptr_glXSendPbufferToVideoNV) ++numFailed;
	return numFailed;
}