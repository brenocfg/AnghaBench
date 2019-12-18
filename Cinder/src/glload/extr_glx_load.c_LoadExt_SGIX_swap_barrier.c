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
typedef  scalar_t__ PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC ;
typedef  scalar_t__ PFNGLXBINDSWAPBARRIERSGIXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glXBindSwapBarrierSGIX ; 
 scalar_t__ _funcptr_glXQueryMaxSwapBarriersSGIX ; 

__attribute__((used)) static int LoadExt_SGIX_swap_barrier()
{
	int numFailed = 0;
	_funcptr_glXBindSwapBarrierSGIX = (PFNGLXBINDSWAPBARRIERSGIXPROC)IntGetProcAddress("glXBindSwapBarrierSGIX");
	if(!_funcptr_glXBindSwapBarrierSGIX) ++numFailed;
	_funcptr_glXQueryMaxSwapBarriersSGIX = (PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)IntGetProcAddress("glXQueryMaxSwapBarriersSGIX");
	if(!_funcptr_glXQueryMaxSwapBarriersSGIX) ++numFailed;
	return numFailed;
}