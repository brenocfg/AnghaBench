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
typedef  scalar_t__ PFNGLGETQUERYOBJECTUI64VEXTPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTI64VEXTPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetQueryObjecti64vEXT ; 
 scalar_t__ _funcptr_glGetQueryObjectui64vEXT ; 

__attribute__((used)) static int LoadExt_EXT_timer_query()
{
	int numFailed = 0;
	_funcptr_glGetQueryObjecti64vEXT = (PFNGLGETQUERYOBJECTI64VEXTPROC)IntGetProcAddress("glGetQueryObjecti64vEXT");
	if(!_funcptr_glGetQueryObjecti64vEXT) ++numFailed;
	_funcptr_glGetQueryObjectui64vEXT = (PFNGLGETQUERYOBJECTUI64VEXTPROC)IntGetProcAddress("glGetQueryObjectui64vEXT");
	if(!_funcptr_glGetQueryObjectui64vEXT) ++numFailed;
	return numFailed;
}