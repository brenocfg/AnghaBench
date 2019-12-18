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
typedef  scalar_t__ PFNGLGETDETAILTEXFUNCSGISPROC ;
typedef  scalar_t__ PFNGLDETAILTEXFUNCSGISPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glDetailTexFuncSGIS ; 
 scalar_t__ _funcptr_glGetDetailTexFuncSGIS ; 

__attribute__((used)) static int LoadExt_SGIS_detail_texture()
{
	int numFailed = 0;
	_funcptr_glDetailTexFuncSGIS = (PFNGLDETAILTEXFUNCSGISPROC)IntGetProcAddress("glDetailTexFuncSGIS");
	if(!_funcptr_glDetailTexFuncSGIS) ++numFailed;
	_funcptr_glGetDetailTexFuncSGIS = (PFNGLGETDETAILTEXFUNCSGISPROC)IntGetProcAddress("glGetDetailTexFuncSGIS");
	if(!_funcptr_glGetDetailTexFuncSGIS) ++numFailed;
	return numFailed;
}