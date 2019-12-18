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
typedef  scalar_t__ PFNWGLMAKECONTEXTCURRENTEXTPROC ;
typedef  scalar_t__ PFNWGLGETCURRENTREADDCEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglGetCurrentReadDCEXT ; 
 scalar_t__ _funcptr_wglMakeContextCurrentEXT ; 

__attribute__((used)) static int LoadExt_EXT_make_current_read()
{
	int numFailed = 0;
	_funcptr_wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)IntGetProcAddress("wglGetCurrentReadDCEXT");
	if(!_funcptr_wglGetCurrentReadDCEXT) ++numFailed;
	_funcptr_wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)IntGetProcAddress("wglMakeContextCurrentEXT");
	if(!_funcptr_wglMakeContextCurrentEXT) ++numFailed;
	return numFailed;
}