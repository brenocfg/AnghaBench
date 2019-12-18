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
typedef  scalar_t__ PFNGLVERTEXATTRIBLFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1I64NVPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLUI64VNVPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLI64VNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetVertexAttribLi64vNV ; 
 scalar_t__ _funcptr_glGetVertexAttribLui64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL1i64NV ; 
 scalar_t__ _funcptr_glVertexAttribL1i64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL1ui64NV ; 
 scalar_t__ _funcptr_glVertexAttribL1ui64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL2i64NV ; 
 scalar_t__ _funcptr_glVertexAttribL2i64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL2ui64NV ; 
 scalar_t__ _funcptr_glVertexAttribL2ui64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL3i64NV ; 
 scalar_t__ _funcptr_glVertexAttribL3i64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL3ui64NV ; 
 scalar_t__ _funcptr_glVertexAttribL3ui64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL4i64NV ; 
 scalar_t__ _funcptr_glVertexAttribL4i64vNV ; 
 scalar_t__ _funcptr_glVertexAttribL4ui64NV ; 
 scalar_t__ _funcptr_glVertexAttribL4ui64vNV ; 
 scalar_t__ _funcptr_glVertexAttribLFormatNV ; 

__attribute__((used)) static int LoadExt_NV_vertex_attrib_integer_64bit()
{
	int numFailed = 0;
	_funcptr_glGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC)IntGetProcAddress("glGetVertexAttribLi64vNV");
	if(!_funcptr_glGetVertexAttribLi64vNV) ++numFailed;
	_funcptr_glGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC)IntGetProcAddress("glGetVertexAttribLui64vNV");
	if(!_funcptr_glGetVertexAttribLui64vNV) ++numFailed;
	_funcptr_glVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC)IntGetProcAddress("glVertexAttribL1i64NV");
	if(!_funcptr_glVertexAttribL1i64NV) ++numFailed;
	_funcptr_glVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC)IntGetProcAddress("glVertexAttribL1i64vNV");
	if(!_funcptr_glVertexAttribL1i64vNV) ++numFailed;
	_funcptr_glVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC)IntGetProcAddress("glVertexAttribL1ui64NV");
	if(!_funcptr_glVertexAttribL1ui64NV) ++numFailed;
	_funcptr_glVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC)IntGetProcAddress("glVertexAttribL1ui64vNV");
	if(!_funcptr_glVertexAttribL1ui64vNV) ++numFailed;
	_funcptr_glVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC)IntGetProcAddress("glVertexAttribL2i64NV");
	if(!_funcptr_glVertexAttribL2i64NV) ++numFailed;
	_funcptr_glVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC)IntGetProcAddress("glVertexAttribL2i64vNV");
	if(!_funcptr_glVertexAttribL2i64vNV) ++numFailed;
	_funcptr_glVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC)IntGetProcAddress("glVertexAttribL2ui64NV");
	if(!_funcptr_glVertexAttribL2ui64NV) ++numFailed;
	_funcptr_glVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC)IntGetProcAddress("glVertexAttribL2ui64vNV");
	if(!_funcptr_glVertexAttribL2ui64vNV) ++numFailed;
	_funcptr_glVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC)IntGetProcAddress("glVertexAttribL3i64NV");
	if(!_funcptr_glVertexAttribL3i64NV) ++numFailed;
	_funcptr_glVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC)IntGetProcAddress("glVertexAttribL3i64vNV");
	if(!_funcptr_glVertexAttribL3i64vNV) ++numFailed;
	_funcptr_glVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC)IntGetProcAddress("glVertexAttribL3ui64NV");
	if(!_funcptr_glVertexAttribL3ui64NV) ++numFailed;
	_funcptr_glVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC)IntGetProcAddress("glVertexAttribL3ui64vNV");
	if(!_funcptr_glVertexAttribL3ui64vNV) ++numFailed;
	_funcptr_glVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC)IntGetProcAddress("glVertexAttribL4i64NV");
	if(!_funcptr_glVertexAttribL4i64NV) ++numFailed;
	_funcptr_glVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC)IntGetProcAddress("glVertexAttribL4i64vNV");
	if(!_funcptr_glVertexAttribL4i64vNV) ++numFailed;
	_funcptr_glVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC)IntGetProcAddress("glVertexAttribL4ui64NV");
	if(!_funcptr_glVertexAttribL4ui64NV) ++numFailed;
	_funcptr_glVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC)IntGetProcAddress("glVertexAttribL4ui64vNV");
	if(!_funcptr_glVertexAttribL4ui64vNV) ++numFailed;
	_funcptr_glVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC)IntGetProcAddress("glVertexAttribLFormatNV");
	if(!_funcptr_glVertexAttribLFormatNV) ++numFailed;
	return numFailed;
}