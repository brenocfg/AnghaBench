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
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISTEXTUREHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISIMAGEHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLGETTEXTURESAMPLERHANDLENVPROC ;
typedef  scalar_t__ PFNGLGETTEXTUREHANDLENVPROC ;
typedef  scalar_t__ PFNGLGETIMAGEHANDLENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetImageHandleNV ; 
 scalar_t__ _funcptr_glGetTextureHandleNV ; 
 scalar_t__ _funcptr_glGetTextureSamplerHandleNV ; 
 scalar_t__ _funcptr_glIsImageHandleResidentNV ; 
 scalar_t__ _funcptr_glIsTextureHandleResidentNV ; 
 scalar_t__ _funcptr_glMakeImageHandleNonResidentNV ; 
 scalar_t__ _funcptr_glMakeImageHandleResidentNV ; 
 scalar_t__ _funcptr_glMakeTextureHandleNonResidentNV ; 
 scalar_t__ _funcptr_glMakeTextureHandleResidentNV ; 
 scalar_t__ _funcptr_glProgramUniformHandleui64NV ; 
 scalar_t__ _funcptr_glProgramUniformHandleui64vNV ; 
 scalar_t__ _funcptr_glUniformHandleui64NV ; 
 scalar_t__ _funcptr_glUniformHandleui64vNV ; 

__attribute__((used)) static int LoadExt_NV_bindless_texture()
{
	int numFailed = 0;
	_funcptr_glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC)IntGetProcAddress("glGetImageHandleNV");
	if(!_funcptr_glGetImageHandleNV) ++numFailed;
	_funcptr_glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC)IntGetProcAddress("glGetTextureHandleNV");
	if(!_funcptr_glGetTextureHandleNV) ++numFailed;
	_funcptr_glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC)IntGetProcAddress("glGetTextureSamplerHandleNV");
	if(!_funcptr_glGetTextureSamplerHandleNV) ++numFailed;
	_funcptr_glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC)IntGetProcAddress("glIsImageHandleResidentNV");
	if(!_funcptr_glIsImageHandleResidentNV) ++numFailed;
	_funcptr_glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC)IntGetProcAddress("glIsTextureHandleResidentNV");
	if(!_funcptr_glIsTextureHandleResidentNV) ++numFailed;
	_funcptr_glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)IntGetProcAddress("glMakeImageHandleNonResidentNV");
	if(!_funcptr_glMakeImageHandleNonResidentNV) ++numFailed;
	_funcptr_glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)IntGetProcAddress("glMakeImageHandleResidentNV");
	if(!_funcptr_glMakeImageHandleResidentNV) ++numFailed;
	_funcptr_glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)IntGetProcAddress("glMakeTextureHandleNonResidentNV");
	if(!_funcptr_glMakeTextureHandleNonResidentNV) ++numFailed;
	_funcptr_glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)IntGetProcAddress("glMakeTextureHandleResidentNV");
	if(!_funcptr_glMakeTextureHandleResidentNV) ++numFailed;
	_funcptr_glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)IntGetProcAddress("glProgramUniformHandleui64NV");
	if(!_funcptr_glProgramUniformHandleui64NV) ++numFailed;
	_funcptr_glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)IntGetProcAddress("glProgramUniformHandleui64vNV");
	if(!_funcptr_glProgramUniformHandleui64vNV) ++numFailed;
	_funcptr_glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC)IntGetProcAddress("glUniformHandleui64NV");
	if(!_funcptr_glUniformHandleui64NV) ++numFailed;
	_funcptr_glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC)IntGetProcAddress("glUniformHandleui64vNV");
	if(!_funcptr_glUniformHandleui64vNV) ++numFailed;
	return numFailed;
}