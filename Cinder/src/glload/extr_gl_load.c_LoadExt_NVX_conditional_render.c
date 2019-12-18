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
typedef  scalar_t__ PFNGLENDCONDITIONALRENDERNVXPROC ;
typedef  scalar_t__ PFNGLBEGINCONDITIONALRENDERNVXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBeginConditionalRenderNVX ; 
 scalar_t__ _funcptr_glEndConditionalRenderNVX ; 

__attribute__((used)) static int LoadExt_NVX_conditional_render()
{
	int numFailed = 0;
	_funcptr_glBeginConditionalRenderNVX = (PFNGLBEGINCONDITIONALRENDERNVXPROC)IntGetProcAddress("glBeginConditionalRenderNVX");
	if(!_funcptr_glBeginConditionalRenderNVX) ++numFailed;
	_funcptr_glEndConditionalRenderNVX = (PFNGLENDCONDITIONALRENDERNVXPROC)IntGetProcAddress("glEndConditionalRenderNVX");
	if(!_funcptr_glEndConditionalRenderNVX) ++numFailed;
	return numFailed;
}