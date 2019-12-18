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
typedef  scalar_t__ PFNGLVERTEXATTRIBLPOINTERPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLDVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetVertexAttribLdv ; 
 scalar_t__ _funcptr_glVertexAttribL1d ; 
 scalar_t__ _funcptr_glVertexAttribL1dv ; 
 scalar_t__ _funcptr_glVertexAttribL2d ; 
 scalar_t__ _funcptr_glVertexAttribL2dv ; 
 scalar_t__ _funcptr_glVertexAttribL3d ; 
 scalar_t__ _funcptr_glVertexAttribL3dv ; 
 scalar_t__ _funcptr_glVertexAttribL4d ; 
 scalar_t__ _funcptr_glVertexAttribL4dv ; 
 scalar_t__ _funcptr_glVertexAttribLPointer ; 

__attribute__((used)) static int LoadExt_ARB_vertex_attrib_64bit()
{
	int numFailed = 0;
	_funcptr_glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)IntGetProcAddress("glGetVertexAttribLdv");
	if(!_funcptr_glGetVertexAttribLdv) ++numFailed;
	_funcptr_glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)IntGetProcAddress("glVertexAttribL1d");
	if(!_funcptr_glVertexAttribL1d) ++numFailed;
	_funcptr_glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)IntGetProcAddress("glVertexAttribL1dv");
	if(!_funcptr_glVertexAttribL1dv) ++numFailed;
	_funcptr_glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)IntGetProcAddress("glVertexAttribL2d");
	if(!_funcptr_glVertexAttribL2d) ++numFailed;
	_funcptr_glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)IntGetProcAddress("glVertexAttribL2dv");
	if(!_funcptr_glVertexAttribL2dv) ++numFailed;
	_funcptr_glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)IntGetProcAddress("glVertexAttribL3d");
	if(!_funcptr_glVertexAttribL3d) ++numFailed;
	_funcptr_glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)IntGetProcAddress("glVertexAttribL3dv");
	if(!_funcptr_glVertexAttribL3dv) ++numFailed;
	_funcptr_glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)IntGetProcAddress("glVertexAttribL4d");
	if(!_funcptr_glVertexAttribL4d) ++numFailed;
	_funcptr_glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)IntGetProcAddress("glVertexAttribL4dv");
	if(!_funcptr_glVertexAttribL4dv) ++numFailed;
	_funcptr_glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)IntGetProcAddress("glVertexAttribLPointer");
	if(!_funcptr_glVertexAttribLPointer) ++numFailed;
	return numFailed;
}