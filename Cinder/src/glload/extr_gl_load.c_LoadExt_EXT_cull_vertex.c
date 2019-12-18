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
typedef  scalar_t__ PFNGLCULLPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLCULLPARAMETERDVEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glCullParameterdvEXT ; 
 scalar_t__ _funcptr_glCullParameterfvEXT ; 

__attribute__((used)) static int LoadExt_EXT_cull_vertex()
{
	int numFailed = 0;
	_funcptr_glCullParameterdvEXT = (PFNGLCULLPARAMETERDVEXTPROC)IntGetProcAddress("glCullParameterdvEXT");
	if(!_funcptr_glCullParameterdvEXT) ++numFailed;
	_funcptr_glCullParameterfvEXT = (PFNGLCULLPARAMETERFVEXTPROC)IntGetProcAddress("glCullParameterfvEXT");
	if(!_funcptr_glCullParameterfvEXT) ++numFailed;
	return numFailed;
}