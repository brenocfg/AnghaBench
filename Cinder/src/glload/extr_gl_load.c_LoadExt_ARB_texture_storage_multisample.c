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
typedef  scalar_t__ PFNGLTEXSTORAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXSTORAGE2DMULTISAMPLEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glTexStorage2DMultisample ; 
 scalar_t__ _funcptr_glTexStorage3DMultisample ; 

__attribute__((used)) static int LoadExt_ARB_texture_storage_multisample()
{
	int numFailed = 0;
	_funcptr_glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage2DMultisample");
	if(!_funcptr_glTexStorage2DMultisample) ++numFailed;
	_funcptr_glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage3DMultisample");
	if(!_funcptr_glTexStorage3DMultisample) ++numFailed;
	return numFailed;
}