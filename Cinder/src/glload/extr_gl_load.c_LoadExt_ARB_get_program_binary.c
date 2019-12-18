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
typedef  scalar_t__ PFNGLPROGRAMPARAMETERIPROC ;
typedef  scalar_t__ PFNGLPROGRAMBINARYPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMBINARYPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetProgramBinary ; 
 scalar_t__ _funcptr_glProgramBinary ; 
 scalar_t__ _funcptr_glProgramParameteri ; 

__attribute__((used)) static int LoadExt_ARB_get_program_binary()
{
	int numFailed = 0;
	_funcptr_glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)IntGetProcAddress("glGetProgramBinary");
	if(!_funcptr_glGetProgramBinary) ++numFailed;
	_funcptr_glProgramBinary = (PFNGLPROGRAMBINARYPROC)IntGetProcAddress("glProgramBinary");
	if(!_funcptr_glProgramBinary) ++numFailed;
	_funcptr_glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)IntGetProcAddress("glProgramParameteri");
	if(!_funcptr_glProgramParameteri) ++numFailed;
	return numFailed;
}