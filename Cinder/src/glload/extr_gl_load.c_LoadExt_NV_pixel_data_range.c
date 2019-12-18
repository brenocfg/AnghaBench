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
typedef  scalar_t__ PFNGLPIXELDATARANGENVPROC ;
typedef  scalar_t__ PFNGLFLUSHPIXELDATARANGENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glFlushPixelDataRangeNV ; 
 scalar_t__ _funcptr_glPixelDataRangeNV ; 

__attribute__((used)) static int LoadExt_NV_pixel_data_range()
{
	int numFailed = 0;
	_funcptr_glFlushPixelDataRangeNV = (PFNGLFLUSHPIXELDATARANGENVPROC)IntGetProcAddress("glFlushPixelDataRangeNV");
	if(!_funcptr_glFlushPixelDataRangeNV) ++numFailed;
	_funcptr_glPixelDataRangeNV = (PFNGLPIXELDATARANGENVPROC)IntGetProcAddress("glPixelDataRangeNV");
	if(!_funcptr_glPixelDataRangeNV) ++numFailed;
	return numFailed;
}