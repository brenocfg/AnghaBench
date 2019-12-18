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
typedef  scalar_t__ PFNGLBINDVERTEXBUFFERSPROC ;
typedef  scalar_t__ PFNGLBINDTEXTURESPROC ;
typedef  scalar_t__ PFNGLBINDSAMPLERSPROC ;
typedef  scalar_t__ PFNGLBINDIMAGETEXTURESPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERSRANGEPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERSBASEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindBuffersBase ; 
 scalar_t__ _funcptr_glBindBuffersRange ; 
 scalar_t__ _funcptr_glBindImageTextures ; 
 scalar_t__ _funcptr_glBindSamplers ; 
 scalar_t__ _funcptr_glBindTextures ; 
 scalar_t__ _funcptr_glBindVertexBuffers ; 

__attribute__((used)) static int LoadExt_ARB_multi_bind()
{
	int numFailed = 0;
	_funcptr_glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)IntGetProcAddress("glBindBuffersBase");
	if(!_funcptr_glBindBuffersBase) ++numFailed;
	_funcptr_glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)IntGetProcAddress("glBindBuffersRange");
	if(!_funcptr_glBindBuffersRange) ++numFailed;
	_funcptr_glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)IntGetProcAddress("glBindImageTextures");
	if(!_funcptr_glBindImageTextures) ++numFailed;
	_funcptr_glBindSamplers = (PFNGLBINDSAMPLERSPROC)IntGetProcAddress("glBindSamplers");
	if(!_funcptr_glBindSamplers) ++numFailed;
	_funcptr_glBindTextures = (PFNGLBINDTEXTURESPROC)IntGetProcAddress("glBindTextures");
	if(!_funcptr_glBindTextures) ++numFailed;
	_funcptr_glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)IntGetProcAddress("glBindVertexBuffers");
	if(!_funcptr_glBindVertexBuffers) ++numFailed;
	return numFailed;
}