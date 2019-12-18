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
typedef  scalar_t__ PFNGLXSET3DFXMODEMESAPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXSet3DfxModeMESA ; 

__attribute__((used)) static int LoadExt_MESA_set_3dfx_mode()
{
	int numFailed = 0;
	_funcptr_glXSet3DfxModeMESA = (PFNGLXSET3DFXMODEMESAPROC)IntGetProcAddress("glXSet3DfxModeMESA");
	if(!_funcptr_glXSet3DfxModeMESA) ++numFailed;
	return numFailed;
}