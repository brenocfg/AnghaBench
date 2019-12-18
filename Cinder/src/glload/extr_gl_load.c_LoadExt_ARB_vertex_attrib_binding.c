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
typedef  scalar_t__ PFNGLVERTEXBINDINGDIVISORPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBLFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBIFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBBINDINGPROC ;
typedef  scalar_t__ PFNGLBINDVERTEXBUFFERPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBindVertexBuffer ; 
 scalar_t__ _funcptr_glVertexAttribBinding ; 
 scalar_t__ _funcptr_glVertexAttribFormat ; 
 scalar_t__ _funcptr_glVertexAttribIFormat ; 
 scalar_t__ _funcptr_glVertexAttribLFormat ; 
 scalar_t__ _funcptr_glVertexBindingDivisor ; 

__attribute__((used)) static int LoadExt_ARB_vertex_attrib_binding()
{
	int numFailed = 0;
	_funcptr_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)IntGetProcAddress("glBindVertexBuffer");
	if(!_funcptr_glBindVertexBuffer) ++numFailed;
	_funcptr_glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)IntGetProcAddress("glVertexAttribBinding");
	if(!_funcptr_glVertexAttribBinding) ++numFailed;
	_funcptr_glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)IntGetProcAddress("glVertexAttribFormat");
	if(!_funcptr_glVertexAttribFormat) ++numFailed;
	_funcptr_glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)IntGetProcAddress("glVertexAttribIFormat");
	if(!_funcptr_glVertexAttribIFormat) ++numFailed;
	_funcptr_glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)IntGetProcAddress("glVertexAttribLFormat");
	if(!_funcptr_glVertexAttribLFormat) ++numFailed;
	_funcptr_glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)IntGetProcAddress("glVertexBindingDivisor");
	if(!_funcptr_glVertexBindingDivisor) ++numFailed;
	return numFailed;
}