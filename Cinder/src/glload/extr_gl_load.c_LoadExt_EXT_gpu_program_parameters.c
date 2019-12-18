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
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERS4FVEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glProgramEnvParameters4fvEXT ; 
 scalar_t__ _funcptr_glProgramLocalParameters4fvEXT ; 

__attribute__((used)) static int LoadExt_EXT_gpu_program_parameters()
{
	int numFailed = 0;
	_funcptr_glProgramEnvParameters4fvEXT = (PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)IntGetProcAddress("glProgramEnvParameters4fvEXT");
	if(!_funcptr_glProgramEnvParameters4fvEXT) ++numFailed;
	_funcptr_glProgramLocalParameters4fvEXT = (PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)IntGetProcAddress("glProgramLocalParameters4fvEXT");
	if(!_funcptr_glProgramLocalParameters4fvEXT) ++numFailed;
	return numFailed;
}