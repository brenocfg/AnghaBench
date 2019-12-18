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
typedef  scalar_t__ PFNGLXSELECTEVENTSGIXPROC ;
typedef  scalar_t__ PFNGLXQUERYGLXPBUFFERSGIXPROC ;
typedef  scalar_t__ PFNGLXGETSELECTEDEVENTSGIXPROC ;
typedef  scalar_t__ PFNGLXDESTROYGLXPBUFFERSGIXPROC ;
typedef  scalar_t__ PFNGLXCREATEGLXPBUFFERSGIXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXCreateGLXPbufferSGIX ; 
 scalar_t__ _funcptr_glXDestroyGLXPbufferSGIX ; 
 scalar_t__ _funcptr_glXGetSelectedEventSGIX ; 
 scalar_t__ _funcptr_glXQueryGLXPbufferSGIX ; 
 scalar_t__ _funcptr_glXSelectEventSGIX ; 

__attribute__((used)) static int LoadExt_SGIX_pbuffer()
{
	int numFailed = 0;
	_funcptr_glXCreateGLXPbufferSGIX = (PFNGLXCREATEGLXPBUFFERSGIXPROC)IntGetProcAddress("glXCreateGLXPbufferSGIX");
	if(!_funcptr_glXCreateGLXPbufferSGIX) ++numFailed;
	_funcptr_glXDestroyGLXPbufferSGIX = (PFNGLXDESTROYGLXPBUFFERSGIXPROC)IntGetProcAddress("glXDestroyGLXPbufferSGIX");
	if(!_funcptr_glXDestroyGLXPbufferSGIX) ++numFailed;
	_funcptr_glXGetSelectedEventSGIX = (PFNGLXGETSELECTEDEVENTSGIXPROC)IntGetProcAddress("glXGetSelectedEventSGIX");
	if(!_funcptr_glXGetSelectedEventSGIX) ++numFailed;
	_funcptr_glXQueryGLXPbufferSGIX = (PFNGLXQUERYGLXPBUFFERSGIXPROC)IntGetProcAddress("glXQueryGLXPbufferSGIX");
	if(!_funcptr_glXQueryGLXPbufferSGIX) ++numFailed;
	_funcptr_glXSelectEventSGIX = (PFNGLXSELECTEVENTSGIXPROC)IntGetProcAddress("glXSelectEventSGIX");
	if(!_funcptr_glXSelectEventSGIX) ++numFailed;
	return numFailed;
}