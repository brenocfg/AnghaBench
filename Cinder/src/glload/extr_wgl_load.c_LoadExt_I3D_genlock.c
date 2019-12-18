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
typedef  scalar_t__ PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLISENABLEDGENLOCKI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEEDGEI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSAMPLERATEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEEDGEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSAMPLERATEI3DPROC ;
typedef  scalar_t__ PFNWGLENABLEGENLOCKI3DPROC ;
typedef  scalar_t__ PFNWGLDISABLEGENLOCKI3DPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglDisableGenlockI3D ; 
 scalar_t__ _funcptr_wglEnableGenlockI3D ; 
 scalar_t__ _funcptr_wglGenlockSampleRateI3D ; 
 scalar_t__ _funcptr_wglGenlockSourceDelayI3D ; 
 scalar_t__ _funcptr_wglGenlockSourceEdgeI3D ; 
 scalar_t__ _funcptr_wglGenlockSourceI3D ; 
 scalar_t__ _funcptr_wglGetGenlockSampleRateI3D ; 
 scalar_t__ _funcptr_wglGetGenlockSourceDelayI3D ; 
 scalar_t__ _funcptr_wglGetGenlockSourceEdgeI3D ; 
 scalar_t__ _funcptr_wglGetGenlockSourceI3D ; 
 scalar_t__ _funcptr_wglIsEnabledGenlockI3D ; 
 scalar_t__ _funcptr_wglQueryGenlockMaxSourceDelayI3D ; 

__attribute__((used)) static int LoadExt_I3D_genlock()
{
	int numFailed = 0;
	_funcptr_wglDisableGenlockI3D = (PFNWGLDISABLEGENLOCKI3DPROC)IntGetProcAddress("wglDisableGenlockI3D");
	if(!_funcptr_wglDisableGenlockI3D) ++numFailed;
	_funcptr_wglEnableGenlockI3D = (PFNWGLENABLEGENLOCKI3DPROC)IntGetProcAddress("wglEnableGenlockI3D");
	if(!_funcptr_wglEnableGenlockI3D) ++numFailed;
	_funcptr_wglGenlockSampleRateI3D = (PFNWGLGENLOCKSAMPLERATEI3DPROC)IntGetProcAddress("wglGenlockSampleRateI3D");
	if(!_funcptr_wglGenlockSampleRateI3D) ++numFailed;
	_funcptr_wglGenlockSourceDelayI3D = (PFNWGLGENLOCKSOURCEDELAYI3DPROC)IntGetProcAddress("wglGenlockSourceDelayI3D");
	if(!_funcptr_wglGenlockSourceDelayI3D) ++numFailed;
	_funcptr_wglGenlockSourceEdgeI3D = (PFNWGLGENLOCKSOURCEEDGEI3DPROC)IntGetProcAddress("wglGenlockSourceEdgeI3D");
	if(!_funcptr_wglGenlockSourceEdgeI3D) ++numFailed;
	_funcptr_wglGenlockSourceI3D = (PFNWGLGENLOCKSOURCEI3DPROC)IntGetProcAddress("wglGenlockSourceI3D");
	if(!_funcptr_wglGenlockSourceI3D) ++numFailed;
	_funcptr_wglGetGenlockSampleRateI3D = (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)IntGetProcAddress("wglGetGenlockSampleRateI3D");
	if(!_funcptr_wglGetGenlockSampleRateI3D) ++numFailed;
	_funcptr_wglGetGenlockSourceDelayI3D = (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)IntGetProcAddress("wglGetGenlockSourceDelayI3D");
	if(!_funcptr_wglGetGenlockSourceDelayI3D) ++numFailed;
	_funcptr_wglGetGenlockSourceEdgeI3D = (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)IntGetProcAddress("wglGetGenlockSourceEdgeI3D");
	if(!_funcptr_wglGetGenlockSourceEdgeI3D) ++numFailed;
	_funcptr_wglGetGenlockSourceI3D = (PFNWGLGETGENLOCKSOURCEI3DPROC)IntGetProcAddress("wglGetGenlockSourceI3D");
	if(!_funcptr_wglGetGenlockSourceI3D) ++numFailed;
	_funcptr_wglIsEnabledGenlockI3D = (PFNWGLISENABLEDGENLOCKI3DPROC)IntGetProcAddress("wglIsEnabledGenlockI3D");
	if(!_funcptr_wglIsEnabledGenlockI3D) ++numFailed;
	_funcptr_wglQueryGenlockMaxSourceDelayI3D = (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)IntGetProcAddress("wglQueryGenlockMaxSourceDelayI3D");
	if(!_funcptr_wglQueryGenlockMaxSourceDelayI3D) ++numFailed;
	return numFailed;
}