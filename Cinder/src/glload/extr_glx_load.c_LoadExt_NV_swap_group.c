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
typedef  scalar_t__ PFNGLXRESETFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNGLXQUERYSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNGLXQUERYMAXSWAPGROUPSNVPROC ;
typedef  scalar_t__ PFNGLXQUERYFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNGLXJOINSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNGLXBINDSWAPBARRIERNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXBindSwapBarrierNV ; 
 scalar_t__ _funcptr_glXJoinSwapGroupNV ; 
 scalar_t__ _funcptr_glXQueryFrameCountNV ; 
 scalar_t__ _funcptr_glXQueryMaxSwapGroupsNV ; 
 scalar_t__ _funcptr_glXQuerySwapGroupNV ; 
 scalar_t__ _funcptr_glXResetFrameCountNV ; 

__attribute__((used)) static int LoadExt_NV_swap_group()
{
	int numFailed = 0;
	_funcptr_glXBindSwapBarrierNV = (PFNGLXBINDSWAPBARRIERNVPROC)IntGetProcAddress("glXBindSwapBarrierNV");
	if(!_funcptr_glXBindSwapBarrierNV) ++numFailed;
	_funcptr_glXJoinSwapGroupNV = (PFNGLXJOINSWAPGROUPNVPROC)IntGetProcAddress("glXJoinSwapGroupNV");
	if(!_funcptr_glXJoinSwapGroupNV) ++numFailed;
	_funcptr_glXQueryFrameCountNV = (PFNGLXQUERYFRAMECOUNTNVPROC)IntGetProcAddress("glXQueryFrameCountNV");
	if(!_funcptr_glXQueryFrameCountNV) ++numFailed;
	_funcptr_glXQueryMaxSwapGroupsNV = (PFNGLXQUERYMAXSWAPGROUPSNVPROC)IntGetProcAddress("glXQueryMaxSwapGroupsNV");
	if(!_funcptr_glXQueryMaxSwapGroupsNV) ++numFailed;
	_funcptr_glXQuerySwapGroupNV = (PFNGLXQUERYSWAPGROUPNVPROC)IntGetProcAddress("glXQuerySwapGroupNV");
	if(!_funcptr_glXQuerySwapGroupNV) ++numFailed;
	_funcptr_glXResetFrameCountNV = (PFNGLXRESETFRAMECOUNTNVPROC)IntGetProcAddress("glXResetFrameCountNV");
	if(!_funcptr_glXResetFrameCountNV) ++numFailed;
	return numFailed;
}