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
typedef  scalar_t__ PFNGLSETFRAGMENTSHADERCONSTANTATIPROC ;
typedef  scalar_t__ PFNGLSAMPLEMAPATIPROC ;
typedef  scalar_t__ PFNGLPASSTEXCOORDATIPROC ;
typedef  scalar_t__ PFNGLGENFRAGMENTSHADERSATIPROC ;
typedef  scalar_t__ PFNGLENDFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLDELETEFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP3ATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP2ATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP1ATIPROC ;
typedef  scalar_t__ PFNGLBINDFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLBEGINFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP3ATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP2ATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP1ATIPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glAlphaFragmentOp1ATI ; 
 scalar_t__ _funcptr_glAlphaFragmentOp2ATI ; 
 scalar_t__ _funcptr_glAlphaFragmentOp3ATI ; 
 scalar_t__ _funcptr_glBeginFragmentShaderATI ; 
 scalar_t__ _funcptr_glBindFragmentShaderATI ; 
 scalar_t__ _funcptr_glColorFragmentOp1ATI ; 
 scalar_t__ _funcptr_glColorFragmentOp2ATI ; 
 scalar_t__ _funcptr_glColorFragmentOp3ATI ; 
 scalar_t__ _funcptr_glDeleteFragmentShaderATI ; 
 scalar_t__ _funcptr_glEndFragmentShaderATI ; 
 scalar_t__ _funcptr_glGenFragmentShadersATI ; 
 scalar_t__ _funcptr_glPassTexCoordATI ; 
 scalar_t__ _funcptr_glSampleMapATI ; 
 scalar_t__ _funcptr_glSetFragmentShaderConstantATI ; 

__attribute__((used)) static int LoadExt_ATI_fragment_shader()
{
	int numFailed = 0;
	_funcptr_glAlphaFragmentOp1ATI = (PFNGLALPHAFRAGMENTOP1ATIPROC)IntGetProcAddress("glAlphaFragmentOp1ATI");
	if(!_funcptr_glAlphaFragmentOp1ATI) ++numFailed;
	_funcptr_glAlphaFragmentOp2ATI = (PFNGLALPHAFRAGMENTOP2ATIPROC)IntGetProcAddress("glAlphaFragmentOp2ATI");
	if(!_funcptr_glAlphaFragmentOp2ATI) ++numFailed;
	_funcptr_glAlphaFragmentOp3ATI = (PFNGLALPHAFRAGMENTOP3ATIPROC)IntGetProcAddress("glAlphaFragmentOp3ATI");
	if(!_funcptr_glAlphaFragmentOp3ATI) ++numFailed;
	_funcptr_glBeginFragmentShaderATI = (PFNGLBEGINFRAGMENTSHADERATIPROC)IntGetProcAddress("glBeginFragmentShaderATI");
	if(!_funcptr_glBeginFragmentShaderATI) ++numFailed;
	_funcptr_glBindFragmentShaderATI = (PFNGLBINDFRAGMENTSHADERATIPROC)IntGetProcAddress("glBindFragmentShaderATI");
	if(!_funcptr_glBindFragmentShaderATI) ++numFailed;
	_funcptr_glColorFragmentOp1ATI = (PFNGLCOLORFRAGMENTOP1ATIPROC)IntGetProcAddress("glColorFragmentOp1ATI");
	if(!_funcptr_glColorFragmentOp1ATI) ++numFailed;
	_funcptr_glColorFragmentOp2ATI = (PFNGLCOLORFRAGMENTOP2ATIPROC)IntGetProcAddress("glColorFragmentOp2ATI");
	if(!_funcptr_glColorFragmentOp2ATI) ++numFailed;
	_funcptr_glColorFragmentOp3ATI = (PFNGLCOLORFRAGMENTOP3ATIPROC)IntGetProcAddress("glColorFragmentOp3ATI");
	if(!_funcptr_glColorFragmentOp3ATI) ++numFailed;
	_funcptr_glDeleteFragmentShaderATI = (PFNGLDELETEFRAGMENTSHADERATIPROC)IntGetProcAddress("glDeleteFragmentShaderATI");
	if(!_funcptr_glDeleteFragmentShaderATI) ++numFailed;
	_funcptr_glEndFragmentShaderATI = (PFNGLENDFRAGMENTSHADERATIPROC)IntGetProcAddress("glEndFragmentShaderATI");
	if(!_funcptr_glEndFragmentShaderATI) ++numFailed;
	_funcptr_glGenFragmentShadersATI = (PFNGLGENFRAGMENTSHADERSATIPROC)IntGetProcAddress("glGenFragmentShadersATI");
	if(!_funcptr_glGenFragmentShadersATI) ++numFailed;
	_funcptr_glPassTexCoordATI = (PFNGLPASSTEXCOORDATIPROC)IntGetProcAddress("glPassTexCoordATI");
	if(!_funcptr_glPassTexCoordATI) ++numFailed;
	_funcptr_glSampleMapATI = (PFNGLSAMPLEMAPATIPROC)IntGetProcAddress("glSampleMapATI");
	if(!_funcptr_glSampleMapATI) ++numFailed;
	_funcptr_glSetFragmentShaderConstantATI = (PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)IntGetProcAddress("glSetFragmentShaderConstantATI");
	if(!_funcptr_glSetFragmentShaderConstantATI) ++numFailed;
	return numFailed;
}