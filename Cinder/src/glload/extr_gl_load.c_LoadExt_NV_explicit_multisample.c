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
typedef  scalar_t__ PFNGLTEXRENDERBUFFERNVPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKINDEXEDNVPROC ;
typedef  scalar_t__ PFNGLGETMULTISAMPLEFVNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetMultisamplefvNV ; 
 scalar_t__ _funcptr_glSampleMaskIndexedNV ; 
 scalar_t__ _funcptr_glTexRenderbufferNV ; 

__attribute__((used)) static int LoadExt_NV_explicit_multisample()
{
	int numFailed = 0;
	_funcptr_glGetMultisamplefvNV = (PFNGLGETMULTISAMPLEFVNVPROC)IntGetProcAddress("glGetMultisamplefvNV");
	if(!_funcptr_glGetMultisamplefvNV) ++numFailed;
	_funcptr_glSampleMaskIndexedNV = (PFNGLSAMPLEMASKINDEXEDNVPROC)IntGetProcAddress("glSampleMaskIndexedNV");
	if(!_funcptr_glSampleMaskIndexedNV) ++numFailed;
	_funcptr_glTexRenderbufferNV = (PFNGLTEXRENDERBUFFERNVPROC)IntGetProcAddress("glTexRenderbufferNV");
	if(!_funcptr_glTexRenderbufferNV) ++numFailed;
	return numFailed;
}