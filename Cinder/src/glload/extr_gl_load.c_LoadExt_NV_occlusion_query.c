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
typedef  scalar_t__ PFNGLISOCCLUSIONQUERYNVPROC ;
typedef  scalar_t__ PFNGLGETOCCLUSIONQUERYUIVNVPROC ;
typedef  scalar_t__ PFNGLGETOCCLUSIONQUERYIVNVPROC ;
typedef  scalar_t__ PFNGLGENOCCLUSIONQUERIESNVPROC ;
typedef  scalar_t__ PFNGLENDOCCLUSIONQUERYNVPROC ;
typedef  scalar_t__ PFNGLDELETEOCCLUSIONQUERIESNVPROC ;
typedef  scalar_t__ PFNGLBEGINOCCLUSIONQUERYNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginOcclusionQueryNV ; 
 scalar_t__ _funcptr_glDeleteOcclusionQueriesNV ; 
 scalar_t__ _funcptr_glEndOcclusionQueryNV ; 
 scalar_t__ _funcptr_glGenOcclusionQueriesNV ; 
 scalar_t__ _funcptr_glGetOcclusionQueryivNV ; 
 scalar_t__ _funcptr_glGetOcclusionQueryuivNV ; 
 scalar_t__ _funcptr_glIsOcclusionQueryNV ; 

__attribute__((used)) static int LoadExt_NV_occlusion_query()
{
	int numFailed = 0;
	_funcptr_glBeginOcclusionQueryNV = (PFNGLBEGINOCCLUSIONQUERYNVPROC)IntGetProcAddress("glBeginOcclusionQueryNV");
	if(!_funcptr_glBeginOcclusionQueryNV) ++numFailed;
	_funcptr_glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC)IntGetProcAddress("glDeleteOcclusionQueriesNV");
	if(!_funcptr_glDeleteOcclusionQueriesNV) ++numFailed;
	_funcptr_glEndOcclusionQueryNV = (PFNGLENDOCCLUSIONQUERYNVPROC)IntGetProcAddress("glEndOcclusionQueryNV");
	if(!_funcptr_glEndOcclusionQueryNV) ++numFailed;
	_funcptr_glGenOcclusionQueriesNV = (PFNGLGENOCCLUSIONQUERIESNVPROC)IntGetProcAddress("glGenOcclusionQueriesNV");
	if(!_funcptr_glGenOcclusionQueriesNV) ++numFailed;
	_funcptr_glGetOcclusionQueryivNV = (PFNGLGETOCCLUSIONQUERYIVNVPROC)IntGetProcAddress("glGetOcclusionQueryivNV");
	if(!_funcptr_glGetOcclusionQueryivNV) ++numFailed;
	_funcptr_glGetOcclusionQueryuivNV = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)IntGetProcAddress("glGetOcclusionQueryuivNV");
	if(!_funcptr_glGetOcclusionQueryuivNV) ++numFailed;
	_funcptr_glIsOcclusionQueryNV = (PFNGLISOCCLUSIONQUERYNVPROC)IntGetProcAddress("glIsOcclusionQueryNV");
	if(!_funcptr_glIsOcclusionQueryNV) ++numFailed;
	return numFailed;
}