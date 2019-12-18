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
typedef  scalar_t__ PFNGLSAMPLEPATTERNSGISPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKSGISPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glSampleMaskSGIS ; 
 scalar_t__ _funcptr_glSamplePatternSGIS ; 

__attribute__((used)) static int LoadExt_SGIS_multisample()
{
	int numFailed = 0;
	_funcptr_glSampleMaskSGIS = (PFNGLSAMPLEMASKSGISPROC)IntGetProcAddress("glSampleMaskSGIS");
	if(!_funcptr_glSampleMaskSGIS) ++numFailed;
	_funcptr_glSamplePatternSGIS = (PFNGLSAMPLEPATTERNSGISPROC)IntGetProcAddress("glSamplePatternSGIS");
	if(!_funcptr_glSamplePatternSGIS) ++numFailed;
	return numFailed;
}