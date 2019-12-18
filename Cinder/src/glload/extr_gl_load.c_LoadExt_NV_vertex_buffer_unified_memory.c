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
typedef  scalar_t__ PFNGLVERTEXFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBIFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBFORMATNVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDFORMATNVPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORFORMATNVPROC ;
typedef  scalar_t__ PFNGLNORMALFORMATNVPROC ;
typedef  scalar_t__ PFNGLINDEXFORMATNVPROC ;
typedef  scalar_t__ PFNGLGETINTEGERUI64I_VNVPROC ;
typedef  scalar_t__ PFNGLFOGCOORDFORMATNVPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGFORMATNVPROC ;
typedef  scalar_t__ PFNGLCOLORFORMATNVPROC ;
typedef  scalar_t__ PFNGLBUFFERADDRESSRANGENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBufferAddressRangeNV ; 
 scalar_t__ _funcptr_glColorFormatNV ; 
 scalar_t__ _funcptr_glEdgeFlagFormatNV ; 
 scalar_t__ _funcptr_glFogCoordFormatNV ; 
 scalar_t__ _funcptr_glGetIntegerui64i_vNV ; 
 scalar_t__ _funcptr_glIndexFormatNV ; 
 scalar_t__ _funcptr_glNormalFormatNV ; 
 scalar_t__ _funcptr_glSecondaryColorFormatNV ; 
 scalar_t__ _funcptr_glTexCoordFormatNV ; 
 scalar_t__ _funcptr_glVertexAttribFormatNV ; 
 scalar_t__ _funcptr_glVertexAttribIFormatNV ; 
 scalar_t__ _funcptr_glVertexFormatNV ; 

__attribute__((used)) static int LoadExt_NV_vertex_buffer_unified_memory()
{
	int numFailed = 0;
	_funcptr_glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)IntGetProcAddress("glBufferAddressRangeNV");
	if(!_funcptr_glBufferAddressRangeNV) ++numFailed;
	_funcptr_glColorFormatNV = (PFNGLCOLORFORMATNVPROC)IntGetProcAddress("glColorFormatNV");
	if(!_funcptr_glColorFormatNV) ++numFailed;
	_funcptr_glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)IntGetProcAddress("glEdgeFlagFormatNV");
	if(!_funcptr_glEdgeFlagFormatNV) ++numFailed;
	_funcptr_glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)IntGetProcAddress("glFogCoordFormatNV");
	if(!_funcptr_glFogCoordFormatNV) ++numFailed;
	_funcptr_glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)IntGetProcAddress("glGetIntegerui64i_vNV");
	if(!_funcptr_glGetIntegerui64i_vNV) ++numFailed;
	_funcptr_glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)IntGetProcAddress("glIndexFormatNV");
	if(!_funcptr_glIndexFormatNV) ++numFailed;
	_funcptr_glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)IntGetProcAddress("glNormalFormatNV");
	if(!_funcptr_glNormalFormatNV) ++numFailed;
	_funcptr_glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)IntGetProcAddress("glSecondaryColorFormatNV");
	if(!_funcptr_glSecondaryColorFormatNV) ++numFailed;
	_funcptr_glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)IntGetProcAddress("glTexCoordFormatNV");
	if(!_funcptr_glTexCoordFormatNV) ++numFailed;
	_funcptr_glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)IntGetProcAddress("glVertexAttribFormatNV");
	if(!_funcptr_glVertexAttribFormatNV) ++numFailed;
	_funcptr_glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)IntGetProcAddress("glVertexAttribIFormatNV");
	if(!_funcptr_glVertexAttribIFormatNV) ++numFailed;
	_funcptr_glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)IntGetProcAddress("glVertexFormatNV");
	if(!_funcptr_glVertexFormatNV) ++numFailed;
	return numFailed;
}