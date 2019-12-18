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
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSINDIRECTPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSINDIRECTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glMultiDrawArraysIndirect ; 
 scalar_t__ _funcptr_glMultiDrawElementsIndirect ; 

__attribute__((used)) static int LoadExt_ARB_multi_draw_indirect()
{
	int numFailed = 0;
	_funcptr_glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glMultiDrawArraysIndirect");
	if(!_funcptr_glMultiDrawArraysIndirect) ++numFailed;
	_funcptr_glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glMultiDrawElementsIndirect");
	if(!_funcptr_glMultiDrawElementsIndirect) ++numFailed;
	return numFailed;
}