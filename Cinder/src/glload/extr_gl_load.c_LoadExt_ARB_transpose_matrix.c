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
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXFARBPROC ;
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXDARBPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXFARBPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXDARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glLoadTransposeMatrixdARB ; 
 scalar_t__ _funcptr_glLoadTransposeMatrixfARB ; 
 scalar_t__ _funcptr_glMultTransposeMatrixdARB ; 
 scalar_t__ _funcptr_glMultTransposeMatrixfARB ; 

__attribute__((used)) static int LoadExt_ARB_transpose_matrix()
{
	int numFailed = 0;
	_funcptr_glLoadTransposeMatrixdARB = (PFNGLLOADTRANSPOSEMATRIXDARBPROC)IntGetProcAddress("glLoadTransposeMatrixdARB");
	if(!_funcptr_glLoadTransposeMatrixdARB) ++numFailed;
	_funcptr_glLoadTransposeMatrixfARB = (PFNGLLOADTRANSPOSEMATRIXFARBPROC)IntGetProcAddress("glLoadTransposeMatrixfARB");
	if(!_funcptr_glLoadTransposeMatrixfARB) ++numFailed;
	_funcptr_glMultTransposeMatrixdARB = (PFNGLMULTTRANSPOSEMATRIXDARBPROC)IntGetProcAddress("glMultTransposeMatrixdARB");
	if(!_funcptr_glMultTransposeMatrixdARB) ++numFailed;
	_funcptr_glMultTransposeMatrixfARB = (PFNGLMULTTRANSPOSEMATRIXFARBPROC)IntGetProcAddress("glMultTransposeMatrixfARB");
	if(!_funcptr_glMultTransposeMatrixfARB) ++numFailed;
	return numFailed;
}