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
typedef  scalar_t__ PFNGLUNMAPTEXTURE2DINTELPROC ;
typedef  scalar_t__ PFNGLSYNCTEXTUREINTELPROC ;
typedef  scalar_t__ PFNGLMAPTEXTURE2DINTELPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glMapTexture2DINTEL ; 
 scalar_t__ _funcptr_glSyncTextureINTEL ; 
 scalar_t__ _funcptr_glUnmapTexture2DINTEL ; 

__attribute__((used)) static int LoadExt_INTEL_map_texture()
{
	int numFailed = 0;
	_funcptr_glMapTexture2DINTEL = (PFNGLMAPTEXTURE2DINTELPROC)IntGetProcAddress("glMapTexture2DINTEL");
	if(!_funcptr_glMapTexture2DINTEL) ++numFailed;
	_funcptr_glSyncTextureINTEL = (PFNGLSYNCTEXTUREINTELPROC)IntGetProcAddress("glSyncTextureINTEL");
	if(!_funcptr_glSyncTextureINTEL) ++numFailed;
	_funcptr_glUnmapTexture2DINTEL = (PFNGLUNMAPTEXTURE2DINTELPROC)IntGetProcAddress("glUnmapTexture2DINTEL");
	if(!_funcptr_glUnmapTexture2DINTEL) ++numFailed;
	return numFailed;
}