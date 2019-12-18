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
typedef  scalar_t__ PFNWGLRESETFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNWGLQUERYSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNWGLQUERYMAXSWAPGROUPSNVPROC ;
typedef  scalar_t__ PFNWGLQUERYFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNWGLJOINSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNWGLBINDSWAPBARRIERNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglBindSwapBarrierNV ; 
 scalar_t__ _funcptr_wglJoinSwapGroupNV ; 
 scalar_t__ _funcptr_wglQueryFrameCountNV ; 
 scalar_t__ _funcptr_wglQueryMaxSwapGroupsNV ; 
 scalar_t__ _funcptr_wglQuerySwapGroupNV ; 
 scalar_t__ _funcptr_wglResetFrameCountNV ; 

__attribute__((used)) static int LoadExt_NV_swap_group()
{
	int numFailed = 0;
	_funcptr_wglBindSwapBarrierNV = (PFNWGLBINDSWAPBARRIERNVPROC)IntGetProcAddress("wglBindSwapBarrierNV");
	if(!_funcptr_wglBindSwapBarrierNV) ++numFailed;
	_funcptr_wglJoinSwapGroupNV = (PFNWGLJOINSWAPGROUPNVPROC)IntGetProcAddress("wglJoinSwapGroupNV");
	if(!_funcptr_wglJoinSwapGroupNV) ++numFailed;
	_funcptr_wglQueryFrameCountNV = (PFNWGLQUERYFRAMECOUNTNVPROC)IntGetProcAddress("wglQueryFrameCountNV");
	if(!_funcptr_wglQueryFrameCountNV) ++numFailed;
	_funcptr_wglQueryMaxSwapGroupsNV = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)IntGetProcAddress("wglQueryMaxSwapGroupsNV");
	if(!_funcptr_wglQueryMaxSwapGroupsNV) ++numFailed;
	_funcptr_wglQuerySwapGroupNV = (PFNWGLQUERYSWAPGROUPNVPROC)IntGetProcAddress("wglQuerySwapGroupNV");
	if(!_funcptr_wglQuerySwapGroupNV) ++numFailed;
	_funcptr_wglResetFrameCountNV = (PFNWGLRESETFRAMECOUNTNVPROC)IntGetProcAddress("wglResetFrameCountNV");
	if(!_funcptr_wglResetFrameCountNV) ++numFailed;
	return numFailed;
}