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
typedef  scalar_t__ PFNGLDRAWELEMENTSINDIRECTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINDIRECTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDrawArraysIndirect ; 
 scalar_t__ _funcptr_glDrawElementsIndirect ; 

__attribute__((used)) static int LoadExt_ARB_draw_indirect()
{
	int numFailed = 0;
	_funcptr_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glDrawArraysIndirect");
	if(!_funcptr_glDrawArraysIndirect) ++numFailed;
	_funcptr_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glDrawElementsIndirect");
	if(!_funcptr_glDrawElementsIndirect) ++numFailed;
	return numFailed;
}