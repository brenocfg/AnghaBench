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
typedef  scalar_t__ PFNGLTEXIMAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE2DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKIPROC ;
typedef  scalar_t__ PFNGLGETMULTISAMPLEFVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetMultisamplefv ; 
 scalar_t__ _funcptr_glSampleMaski ; 
 scalar_t__ _funcptr_glTexImage2DMultisample ; 
 scalar_t__ _funcptr_glTexImage3DMultisample ; 

__attribute__((used)) static int LoadExt_ARB_texture_multisample()
{
	int numFailed = 0;
	_funcptr_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)IntGetProcAddress("glGetMultisamplefv");
	if(!_funcptr_glGetMultisamplefv) ++numFailed;
	_funcptr_glSampleMaski = (PFNGLSAMPLEMASKIPROC)IntGetProcAddress("glSampleMaski");
	if(!_funcptr_glSampleMaski) ++numFailed;
	_funcptr_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexImage2DMultisample");
	if(!_funcptr_glTexImage2DMultisample) ++numFailed;
	_funcptr_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexImage3DMultisample");
	if(!_funcptr_glTexImage3DMultisample) ++numFailed;
	return numFailed;
}