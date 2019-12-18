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
typedef  scalar_t__ PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLCOMBINERSTAGEPARAMETERFVNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glCombinerStageParameterfvNV ; 
 scalar_t__ _funcptr_glGetCombinerStageParameterfvNV ; 

__attribute__((used)) static int LoadExt_NV_register_combiners2()
{
	int numFailed = 0;
	_funcptr_glCombinerStageParameterfvNV = (PFNGLCOMBINERSTAGEPARAMETERFVNVPROC)IntGetProcAddress("glCombinerStageParameterfvNV");
	if(!_funcptr_glCombinerStageParameterfvNV) ++numFailed;
	_funcptr_glGetCombinerStageParameterfvNV = (PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC)IntGetProcAddress("glGetCombinerStageParameterfvNV");
	if(!_funcptr_glGetCombinerStageParameterfvNV) ++numFailed;
	return numFailed;
}