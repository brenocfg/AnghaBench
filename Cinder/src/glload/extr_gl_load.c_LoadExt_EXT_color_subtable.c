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
typedef  scalar_t__ PFNGLCOPYCOLORSUBTABLEEXTPROC ;
typedef  scalar_t__ PFNGLCOLORSUBTABLEEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glColorSubTableEXT ; 
 scalar_t__ _funcptr_glCopyColorSubTableEXT ; 

__attribute__((used)) static int LoadExt_EXT_color_subtable()
{
	int numFailed = 0;
	_funcptr_glColorSubTableEXT = (PFNGLCOLORSUBTABLEEXTPROC)IntGetProcAddress("glColorSubTableEXT");
	if(!_funcptr_glColorSubTableEXT) ++numFailed;
	_funcptr_glCopyColorSubTableEXT = (PFNGLCOPYCOLORSUBTABLEEXTPROC)IntGetProcAddress("glCopyColorSubTableEXT");
	if(!_funcptr_glCopyColorSubTableEXT) ++numFailed;
	return numFailed;
}