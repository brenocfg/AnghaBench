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
typedef  scalar_t__ PFNGLXWAITVIDEOSYNCSGIPROC ;
typedef  scalar_t__ PFNGLXGETVIDEOSYNCSGIPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXGetVideoSyncSGI ; 
 scalar_t__ _funcptr_glXWaitVideoSyncSGI ; 

__attribute__((used)) static int LoadExt_SGI_video_sync()
{
	int numFailed = 0;
	_funcptr_glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGIPROC)IntGetProcAddress("glXGetVideoSyncSGI");
	if(!_funcptr_glXGetVideoSyncSGI) ++numFailed;
	_funcptr_glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGIPROC)IntGetProcAddress("glXWaitVideoSyncSGI");
	if(!_funcptr_glXWaitVideoSyncSGI) ++numFailed;
	return numFailed;
}