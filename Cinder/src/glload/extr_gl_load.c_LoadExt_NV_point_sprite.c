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
typedef  scalar_t__ PFNGLPOINTPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERINVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glPointParameteriNV ; 
 scalar_t__ _funcptr_glPointParameterivNV ; 

__attribute__((used)) static int LoadExt_NV_point_sprite()
{
	int numFailed = 0;
	_funcptr_glPointParameteriNV = (PFNGLPOINTPARAMETERINVPROC)IntGetProcAddress("glPointParameteriNV");
	if(!_funcptr_glPointParameteriNV) ++numFailed;
	_funcptr_glPointParameterivNV = (PFNGLPOINTPARAMETERIVNVPROC)IntGetProcAddress("glPointParameterivNV");
	if(!_funcptr_glPointParameterivNV) ++numFailed;
	return numFailed;
}