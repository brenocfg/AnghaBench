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
typedef  scalar_t__ PFNGLWINDOWPOS3SVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3SARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glWindowPos2dARB ; 
 scalar_t__ _funcptr_glWindowPos2dvARB ; 
 scalar_t__ _funcptr_glWindowPos2fARB ; 
 scalar_t__ _funcptr_glWindowPos2fvARB ; 
 scalar_t__ _funcptr_glWindowPos2iARB ; 
 scalar_t__ _funcptr_glWindowPos2ivARB ; 
 scalar_t__ _funcptr_glWindowPos2sARB ; 
 scalar_t__ _funcptr_glWindowPos2svARB ; 
 scalar_t__ _funcptr_glWindowPos3dARB ; 
 scalar_t__ _funcptr_glWindowPos3dvARB ; 
 scalar_t__ _funcptr_glWindowPos3fARB ; 
 scalar_t__ _funcptr_glWindowPos3fvARB ; 
 scalar_t__ _funcptr_glWindowPos3iARB ; 
 scalar_t__ _funcptr_glWindowPos3ivARB ; 
 scalar_t__ _funcptr_glWindowPos3sARB ; 
 scalar_t__ _funcptr_glWindowPos3svARB ; 

__attribute__((used)) static int LoadExt_ARB_window_pos()
{
	int numFailed = 0;
	_funcptr_glWindowPos2dARB = (PFNGLWINDOWPOS2DARBPROC)IntGetProcAddress("glWindowPos2dARB");
	if(!_funcptr_glWindowPos2dARB) ++numFailed;
	_funcptr_glWindowPos2dvARB = (PFNGLWINDOWPOS2DVARBPROC)IntGetProcAddress("glWindowPos2dvARB");
	if(!_funcptr_glWindowPos2dvARB) ++numFailed;
	_funcptr_glWindowPos2fARB = (PFNGLWINDOWPOS2FARBPROC)IntGetProcAddress("glWindowPos2fARB");
	if(!_funcptr_glWindowPos2fARB) ++numFailed;
	_funcptr_glWindowPos2fvARB = (PFNGLWINDOWPOS2FVARBPROC)IntGetProcAddress("glWindowPos2fvARB");
	if(!_funcptr_glWindowPos2fvARB) ++numFailed;
	_funcptr_glWindowPos2iARB = (PFNGLWINDOWPOS2IARBPROC)IntGetProcAddress("glWindowPos2iARB");
	if(!_funcptr_glWindowPos2iARB) ++numFailed;
	_funcptr_glWindowPos2ivARB = (PFNGLWINDOWPOS2IVARBPROC)IntGetProcAddress("glWindowPos2ivARB");
	if(!_funcptr_glWindowPos2ivARB) ++numFailed;
	_funcptr_glWindowPos2sARB = (PFNGLWINDOWPOS2SARBPROC)IntGetProcAddress("glWindowPos2sARB");
	if(!_funcptr_glWindowPos2sARB) ++numFailed;
	_funcptr_glWindowPos2svARB = (PFNGLWINDOWPOS2SVARBPROC)IntGetProcAddress("glWindowPos2svARB");
	if(!_funcptr_glWindowPos2svARB) ++numFailed;
	_funcptr_glWindowPos3dARB = (PFNGLWINDOWPOS3DARBPROC)IntGetProcAddress("glWindowPos3dARB");
	if(!_funcptr_glWindowPos3dARB) ++numFailed;
	_funcptr_glWindowPos3dvARB = (PFNGLWINDOWPOS3DVARBPROC)IntGetProcAddress("glWindowPos3dvARB");
	if(!_funcptr_glWindowPos3dvARB) ++numFailed;
	_funcptr_glWindowPos3fARB = (PFNGLWINDOWPOS3FARBPROC)IntGetProcAddress("glWindowPos3fARB");
	if(!_funcptr_glWindowPos3fARB) ++numFailed;
	_funcptr_glWindowPos3fvARB = (PFNGLWINDOWPOS3FVARBPROC)IntGetProcAddress("glWindowPos3fvARB");
	if(!_funcptr_glWindowPos3fvARB) ++numFailed;
	_funcptr_glWindowPos3iARB = (PFNGLWINDOWPOS3IARBPROC)IntGetProcAddress("glWindowPos3iARB");
	if(!_funcptr_glWindowPos3iARB) ++numFailed;
	_funcptr_glWindowPos3ivARB = (PFNGLWINDOWPOS3IVARBPROC)IntGetProcAddress("glWindowPos3ivARB");
	if(!_funcptr_glWindowPos3ivARB) ++numFailed;
	_funcptr_glWindowPos3sARB = (PFNGLWINDOWPOS3SARBPROC)IntGetProcAddress("glWindowPos3sARB");
	if(!_funcptr_glWindowPos3sARB) ++numFailed;
	_funcptr_glWindowPos3svARB = (PFNGLWINDOWPOS3SVARBPROC)IntGetProcAddress("glWindowPos3svARB");
	if(!_funcptr_glWindowPos3svARB) ++numFailed;
	return numFailed;
}