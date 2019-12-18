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
typedef  scalar_t__ PFNGLENDCONDITIONALRENDERNVPROC ;
typedef  scalar_t__ PFNGLBEGINCONDITIONALRENDERNVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginConditionalRenderNV ; 
 scalar_t__ _funcptr_glEndConditionalRenderNV ; 

__attribute__((used)) static int LoadExt_NV_conditional_render()
{
	int numFailed = 0;
	_funcptr_glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)IntGetProcAddress("glBeginConditionalRenderNV");
	if(!_funcptr_glBeginConditionalRenderNV) ++numFailed;
	_funcptr_glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)IntGetProcAddress("glEndConditionalRenderNV");
	if(!_funcptr_glEndConditionalRenderNV) ++numFailed;
	return numFailed;
}