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
typedef  scalar_t__ PFNGLORTHOFOESPROC ;
typedef  scalar_t__ PFNGLGETCLIPPLANEFOESPROC ;
typedef  scalar_t__ PFNGLFRUSTUMFOESPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEFOESPROC ;
typedef  scalar_t__ PFNGLCLIPPLANEFOESPROC ;
typedef  scalar_t__ PFNGLCLEARDEPTHFOESPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glClearDepthfOES ; 
 scalar_t__ _funcptr_glClipPlanefOES ; 
 scalar_t__ _funcptr_glDepthRangefOES ; 
 scalar_t__ _funcptr_glFrustumfOES ; 
 scalar_t__ _funcptr_glGetClipPlanefOES ; 
 scalar_t__ _funcptr_glOrthofOES ; 

__attribute__((used)) static int LoadExt_OES_single_precision()
{
	int numFailed = 0;
	_funcptr_glClearDepthfOES = (PFNGLCLEARDEPTHFOESPROC)IntGetProcAddress("glClearDepthfOES");
	if(!_funcptr_glClearDepthfOES) ++numFailed;
	_funcptr_glClipPlanefOES = (PFNGLCLIPPLANEFOESPROC)IntGetProcAddress("glClipPlanefOES");
	if(!_funcptr_glClipPlanefOES) ++numFailed;
	_funcptr_glDepthRangefOES = (PFNGLDEPTHRANGEFOESPROC)IntGetProcAddress("glDepthRangefOES");
	if(!_funcptr_glDepthRangefOES) ++numFailed;
	_funcptr_glFrustumfOES = (PFNGLFRUSTUMFOESPROC)IntGetProcAddress("glFrustumfOES");
	if(!_funcptr_glFrustumfOES) ++numFailed;
	_funcptr_glGetClipPlanefOES = (PFNGLGETCLIPPLANEFOESPROC)IntGetProcAddress("glGetClipPlanefOES");
	if(!_funcptr_glGetClipPlanefOES) ++numFailed;
	_funcptr_glOrthofOES = (PFNGLORTHOFOESPROC)IntGetProcAddress("glOrthofOES");
	if(!_funcptr_glOrthofOES) ++numFailed;
	return numFailed;
}