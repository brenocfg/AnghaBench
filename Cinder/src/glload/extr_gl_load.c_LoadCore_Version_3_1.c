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
typedef  scalar_t__ PFNGLUNIFORMBLOCKBINDINGPROC ;
typedef  scalar_t__ PFNGLTEXBUFFERPROC ;
typedef  scalar_t__ PFNGLPRIMITIVERESTARTINDEXPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMINDICESPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMBLOCKINDEXPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMSIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKIVPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINSTANCEDPROC ;
typedef  scalar_t__ PFNGLCOPYBUFFERSUBDATAPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glCopyBufferSubData ; 
 scalar_t__ _funcptr_glDrawArraysInstanced ; 
 scalar_t__ _funcptr_glDrawElementsInstanced ; 
 scalar_t__ _funcptr_glGetActiveUniformBlockName ; 
 scalar_t__ _funcptr_glGetActiveUniformBlockiv ; 
 scalar_t__ _funcptr_glGetActiveUniformName ; 
 scalar_t__ _funcptr_glGetActiveUniformsiv ; 
 scalar_t__ _funcptr_glGetUniformBlockIndex ; 
 scalar_t__ _funcptr_glGetUniformIndices ; 
 scalar_t__ _funcptr_glPrimitiveRestartIndex ; 
 scalar_t__ _funcptr_glTexBuffer ; 
 scalar_t__ _funcptr_glUniformBlockBinding ; 

__attribute__((used)) static int LoadCore_Version_3_1()
{
	int numFailed = 0;
	_funcptr_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)IntGetProcAddress("glCopyBufferSubData");
	if(!_funcptr_glCopyBufferSubData) ++numFailed;
	_funcptr_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)IntGetProcAddress("glDrawArraysInstanced");
	if(!_funcptr_glDrawArraysInstanced) ++numFailed;
	_funcptr_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)IntGetProcAddress("glDrawElementsInstanced");
	if(!_funcptr_glDrawElementsInstanced) ++numFailed;
	_funcptr_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)IntGetProcAddress("glGetActiveUniformBlockName");
	if(!_funcptr_glGetActiveUniformBlockName) ++numFailed;
	_funcptr_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)IntGetProcAddress("glGetActiveUniformBlockiv");
	if(!_funcptr_glGetActiveUniformBlockiv) ++numFailed;
	_funcptr_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveUniformName");
	if(!_funcptr_glGetActiveUniformName) ++numFailed;
	_funcptr_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)IntGetProcAddress("glGetActiveUniformsiv");
	if(!_funcptr_glGetActiveUniformsiv) ++numFailed;
	_funcptr_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)IntGetProcAddress("glGetUniformBlockIndex");
	if(!_funcptr_glGetUniformBlockIndex) ++numFailed;
	_funcptr_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)IntGetProcAddress("glGetUniformIndices");
	if(!_funcptr_glGetUniformIndices) ++numFailed;
	_funcptr_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)IntGetProcAddress("glPrimitiveRestartIndex");
	if(!_funcptr_glPrimitiveRestartIndex) ++numFailed;
	_funcptr_glTexBuffer = (PFNGLTEXBUFFERPROC)IntGetProcAddress("glTexBuffer");
	if(!_funcptr_glTexBuffer) ++numFailed;
	_funcptr_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)IntGetProcAddress("glUniformBlockBinding");
	if(!_funcptr_glUniformBlockBinding) ++numFailed;
	return numFailed;
}