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
typedef  scalar_t__ PFNGLQUERYCOUNTERPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTUI64VPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTI64VPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glGetQueryObjecti64v ; 
 scalar_t__ _funcptr_glGetQueryObjectui64v ; 
 scalar_t__ _funcptr_glQueryCounter ; 

__attribute__((used)) static int LoadExt_ARB_timer_query()
{
	int numFailed = 0;
	_funcptr_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)IntGetProcAddress("glGetQueryObjecti64v");
	if(!_funcptr_glGetQueryObjecti64v) ++numFailed;
	_funcptr_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)IntGetProcAddress("glGetQueryObjectui64v");
	if(!_funcptr_glGetQueryObjectui64v) ++numFailed;
	_funcptr_glQueryCounter = (PFNGLQUERYCOUNTERPROC)IntGetProcAddress("glQueryCounter");
	if(!_funcptr_glQueryCounter) ++numFailed;
	return numFailed;
}