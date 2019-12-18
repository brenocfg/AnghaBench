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
typedef  scalar_t__ PFNGLUNIFORMSUBROUTINESUIVPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMSUBROUTINEUIVPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEINDEXPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMSTAGEIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINENAMEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetActiveSubroutineName ; 
 scalar_t__ _funcptr_glGetActiveSubroutineUniformName ; 
 scalar_t__ _funcptr_glGetActiveSubroutineUniformiv ; 
 scalar_t__ _funcptr_glGetProgramStageiv ; 
 scalar_t__ _funcptr_glGetSubroutineIndex ; 
 scalar_t__ _funcptr_glGetSubroutineUniformLocation ; 
 scalar_t__ _funcptr_glGetUniformSubroutineuiv ; 
 scalar_t__ _funcptr_glUniformSubroutinesuiv ; 

__attribute__((used)) static int LoadExt_ARB_shader_subroutine()
{
	int numFailed = 0;
	_funcptr_glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)IntGetProcAddress("glGetActiveSubroutineName");
	if(!_funcptr_glGetActiveSubroutineName) ++numFailed;
	_funcptr_glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveSubroutineUniformName");
	if(!_funcptr_glGetActiveSubroutineUniformName) ++numFailed;
	_funcptr_glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)IntGetProcAddress("glGetActiveSubroutineUniformiv");
	if(!_funcptr_glGetActiveSubroutineUniformiv) ++numFailed;
	_funcptr_glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)IntGetProcAddress("glGetProgramStageiv");
	if(!_funcptr_glGetProgramStageiv) ++numFailed;
	_funcptr_glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)IntGetProcAddress("glGetSubroutineIndex");
	if(!_funcptr_glGetSubroutineIndex) ++numFailed;
	_funcptr_glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)IntGetProcAddress("glGetSubroutineUniformLocation");
	if(!_funcptr_glGetSubroutineUniformLocation) ++numFailed;
	_funcptr_glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)IntGetProcAddress("glGetUniformSubroutineuiv");
	if(!_funcptr_glGetUniformSubroutineuiv) ++numFailed;
	_funcptr_glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)IntGetProcAddress("glUniformSubroutinesuiv");
	if(!_funcptr_glUniformSubroutinesuiv) ++numFailed;
	return numFailed;
}