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
typedef  scalar_t__ PFNGLUSESHADERPROGRAMEXTPROC ;
typedef  scalar_t__ PFNGLCREATESHADERPROGRAMEXTPROC ;
typedef  scalar_t__ PFNGLACTIVEPROGRAMEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glActiveProgramEXT ; 
 scalar_t__ _funcptr_glCreateShaderProgramEXT ; 
 scalar_t__ _funcptr_glUseShaderProgramEXT ; 

__attribute__((used)) static int LoadExt_EXT_separate_shader_objects()
{
	int numFailed = 0;
	_funcptr_glActiveProgramEXT = (PFNGLACTIVEPROGRAMEXTPROC)IntGetProcAddress("glActiveProgramEXT");
	if(!_funcptr_glActiveProgramEXT) ++numFailed;
	_funcptr_glCreateShaderProgramEXT = (PFNGLCREATESHADERPROGRAMEXTPROC)IntGetProcAddress("glCreateShaderProgramEXT");
	if(!_funcptr_glCreateShaderProgramEXT) ++numFailed;
	_funcptr_glUseShaderProgramEXT = (PFNGLUSESHADERPROGRAMEXTPROC)IntGetProcAddress("glUseShaderProgramEXT");
	if(!_funcptr_glUseShaderProgramEXT) ++numFailed;
	return numFailed;
}