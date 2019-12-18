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
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB2FAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB2DAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB1FAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB1DAPPLEPROC ;
typedef  scalar_t__ PFNGLISVERTEXATTRIBENABLEDAPPLEPROC ;
typedef  scalar_t__ PFNGLENABLEVERTEXATTRIBAPPLEPROC ;
typedef  scalar_t__ PFNGLDISABLEVERTEXATTRIBAPPLEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDisableVertexAttribAPPLE ; 
 scalar_t__ _funcptr_glEnableVertexAttribAPPLE ; 
 scalar_t__ _funcptr_glIsVertexAttribEnabledAPPLE ; 
 scalar_t__ _funcptr_glMapVertexAttrib1dAPPLE ; 
 scalar_t__ _funcptr_glMapVertexAttrib1fAPPLE ; 
 scalar_t__ _funcptr_glMapVertexAttrib2dAPPLE ; 
 scalar_t__ _funcptr_glMapVertexAttrib2fAPPLE ; 

__attribute__((used)) static int LoadExt_APPLE_vertex_program_evaluators()
{
	int numFailed = 0;
	_funcptr_glDisableVertexAttribAPPLE = (PFNGLDISABLEVERTEXATTRIBAPPLEPROC)IntGetProcAddress("glDisableVertexAttribAPPLE");
	if(!_funcptr_glDisableVertexAttribAPPLE) ++numFailed;
	_funcptr_glEnableVertexAttribAPPLE = (PFNGLENABLEVERTEXATTRIBAPPLEPROC)IntGetProcAddress("glEnableVertexAttribAPPLE");
	if(!_funcptr_glEnableVertexAttribAPPLE) ++numFailed;
	_funcptr_glIsVertexAttribEnabledAPPLE = (PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)IntGetProcAddress("glIsVertexAttribEnabledAPPLE");
	if(!_funcptr_glIsVertexAttribEnabledAPPLE) ++numFailed;
	_funcptr_glMapVertexAttrib1dAPPLE = (PFNGLMAPVERTEXATTRIB1DAPPLEPROC)IntGetProcAddress("glMapVertexAttrib1dAPPLE");
	if(!_funcptr_glMapVertexAttrib1dAPPLE) ++numFailed;
	_funcptr_glMapVertexAttrib1fAPPLE = (PFNGLMAPVERTEXATTRIB1FAPPLEPROC)IntGetProcAddress("glMapVertexAttrib1fAPPLE");
	if(!_funcptr_glMapVertexAttrib1fAPPLE) ++numFailed;
	_funcptr_glMapVertexAttrib2dAPPLE = (PFNGLMAPVERTEXATTRIB2DAPPLEPROC)IntGetProcAddress("glMapVertexAttrib2dAPPLE");
	if(!_funcptr_glMapVertexAttrib2dAPPLE) ++numFailed;
	_funcptr_glMapVertexAttrib2fAPPLE = (PFNGLMAPVERTEXATTRIB2FAPPLEPROC)IntGetProcAddress("glMapVertexAttrib2fAPPLE");
	if(!_funcptr_glMapVertexAttrib2fAPPLE) ++numFailed;
	return numFailed;
}