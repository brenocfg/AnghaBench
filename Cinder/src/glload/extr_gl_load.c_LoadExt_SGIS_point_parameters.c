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
typedef  scalar_t__ PFNGLPOINTPARAMETERFVSGISPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFSGISPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glPointParameterfSGIS ; 
 scalar_t__ _funcptr_glPointParameterfvSGIS ; 

__attribute__((used)) static int LoadExt_SGIS_point_parameters()
{
	int numFailed = 0;
	_funcptr_glPointParameterfSGIS = (PFNGLPOINTPARAMETERFSGISPROC)IntGetProcAddress("glPointParameterfSGIS");
	if(!_funcptr_glPointParameterfSGIS) ++numFailed;
	_funcptr_glPointParameterfvSGIS = (PFNGLPOINTPARAMETERFVSGISPROC)IntGetProcAddress("glPointParameterfvSGIS");
	if(!_funcptr_glPointParameterfvSGIS) ++numFailed;
	return numFailed;
}