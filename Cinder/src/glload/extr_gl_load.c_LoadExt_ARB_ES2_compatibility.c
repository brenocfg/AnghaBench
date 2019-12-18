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
typedef  scalar_t__ PFNGLSHADERBINARYPROC ;
typedef  scalar_t__ PFNGLRELEASESHADERCOMPILERPROC ;
typedef  scalar_t__ PFNGLGETSHADERPRECISIONFORMATPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEFPROC ;
typedef  scalar_t__ PFNGLCLEARDEPTHFPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glClearDepthf ; 
 scalar_t__ _funcptr_glDepthRangef ; 
 scalar_t__ _funcptr_glGetShaderPrecisionFormat ; 
 scalar_t__ _funcptr_glReleaseShaderCompiler ; 
 scalar_t__ _funcptr_glShaderBinary ; 

__attribute__((used)) static int LoadExt_ARB_ES2_compatibility()
{
	int numFailed = 0;
	_funcptr_glClearDepthf = (PFNGLCLEARDEPTHFPROC)IntGetProcAddress("glClearDepthf");
	if(!_funcptr_glClearDepthf) ++numFailed;
	_funcptr_glDepthRangef = (PFNGLDEPTHRANGEFPROC)IntGetProcAddress("glDepthRangef");
	if(!_funcptr_glDepthRangef) ++numFailed;
	_funcptr_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)IntGetProcAddress("glGetShaderPrecisionFormat");
	if(!_funcptr_glGetShaderPrecisionFormat) ++numFailed;
	_funcptr_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)IntGetProcAddress("glReleaseShaderCompiler");
	if(!_funcptr_glReleaseShaderCompiler) ++numFailed;
	_funcptr_glShaderBinary = (PFNGLSHADERBINARYPROC)IntGetProcAddress("glShaderBinary");
	if(!_funcptr_glShaderBinary) ++numFailed;
	return numFailed;
}