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
typedef  scalar_t__ PFNGLPATCHPARAMETERIPROC ;
typedef  scalar_t__ PFNGLPATCHPARAMETERFVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glPatchParameterfv ; 
 scalar_t__ _funcptr_glPatchParameteri ; 

__attribute__((used)) static int LoadExt_ARB_tessellation_shader()
{
	int numFailed = 0;
	_funcptr_glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)IntGetProcAddress("glPatchParameterfv");
	if(!_funcptr_glPatchParameterfv) ++numFailed;
	_funcptr_glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)IntGetProcAddress("glPatchParameteri");
	if(!_funcptr_glPatchParameteri) ++numFailed;
	return numFailed;
}