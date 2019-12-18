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
typedef  scalar_t__ PFNGLMULTIMODEDRAWELEMENTSIBMPROC ;
typedef  scalar_t__ PFNGLMULTIMODEDRAWARRAYSIBMPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glMultiModeDrawArraysIBM ; 
 scalar_t__ _funcptr_glMultiModeDrawElementsIBM ; 

__attribute__((used)) static int LoadExt_IBM_multimode_draw_arrays()
{
	int numFailed = 0;
	_funcptr_glMultiModeDrawArraysIBM = (PFNGLMULTIMODEDRAWARRAYSIBMPROC)IntGetProcAddress("glMultiModeDrawArraysIBM");
	if(!_funcptr_glMultiModeDrawArraysIBM) ++numFailed;
	_funcptr_glMultiModeDrawElementsIBM = (PFNGLMULTIMODEDRAWELEMENTSIBMPROC)IntGetProcAddress("glMultiModeDrawElementsIBM");
	if(!_funcptr_glMultiModeDrawElementsIBM) ++numFailed;
	return numFailed;
}