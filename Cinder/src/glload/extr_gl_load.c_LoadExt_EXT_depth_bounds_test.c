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
typedef  scalar_t__ PFNGLDEPTHBOUNDSEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDepthBoundsEXT ; 

__attribute__((used)) static int LoadExt_EXT_depth_bounds_test()
{
	int numFailed = 0;
	_funcptr_glDepthBoundsEXT = (PFNGLDEPTHBOUNDSEXTPROC)IntGetProcAddress("glDepthBoundsEXT");
	if(!_funcptr_glDepthBoundsEXT) ++numFailed;
	return numFailed;
}