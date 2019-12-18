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
typedef  scalar_t__ PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMATIONMAP3FSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMATIONMAP3DSGIXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDeformSGIX ; 
 scalar_t__ _funcptr_glDeformationMap3dSGIX ; 
 scalar_t__ _funcptr_glDeformationMap3fSGIX ; 
 scalar_t__ _funcptr_glLoadIdentityDeformationMapSGIX ; 

__attribute__((used)) static int LoadExt_SGIX_polynomial_ffd()
{
	int numFailed = 0;
	_funcptr_glDeformSGIX = (PFNGLDEFORMSGIXPROC)IntGetProcAddress("glDeformSGIX");
	if(!_funcptr_glDeformSGIX) ++numFailed;
	_funcptr_glDeformationMap3dSGIX = (PFNGLDEFORMATIONMAP3DSGIXPROC)IntGetProcAddress("glDeformationMap3dSGIX");
	if(!_funcptr_glDeformationMap3dSGIX) ++numFailed;
	_funcptr_glDeformationMap3fSGIX = (PFNGLDEFORMATIONMAP3FSGIXPROC)IntGetProcAddress("glDeformationMap3fSGIX");
	if(!_funcptr_glDeformationMap3fSGIX) ++numFailed;
	_funcptr_glLoadIdentityDeformationMapSGIX = (PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)IntGetProcAddress("glLoadIdentityDeformationMapSGIX");
	if(!_funcptr_glLoadIdentityDeformationMapSGIX) ++numFailed;
	return numFailed;
}