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
typedef  scalar_t__ PFNGLPROGRAMPARAMETERIARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURELAYERARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREFACEARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glFramebufferTextureARB ; 
 scalar_t__ _funcptr_glFramebufferTextureFaceARB ; 
 scalar_t__ _funcptr_glFramebufferTextureLayerARB ; 
 scalar_t__ _funcptr_glProgramParameteriARB ; 

__attribute__((used)) static int LoadExt_ARB_geometry_shader4()
{
	int numFailed = 0;
	_funcptr_glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC)IntGetProcAddress("glFramebufferTextureARB");
	if(!_funcptr_glFramebufferTextureARB) ++numFailed;
	_funcptr_glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)IntGetProcAddress("glFramebufferTextureFaceARB");
	if(!_funcptr_glFramebufferTextureFaceARB) ++numFailed;
	_funcptr_glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)IntGetProcAddress("glFramebufferTextureLayerARB");
	if(!_funcptr_glFramebufferTextureLayerARB) ++numFailed;
	_funcptr_glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)IntGetProcAddress("glProgramParameteriARB");
	if(!_funcptr_glProgramParameteriARB) ++numFailed;
	return numFailed;
}