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
typedef  scalar_t__ PFNGLSTRINGMARKERGREMEDYPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glStringMarkerGREMEDY ; 

__attribute__((used)) static int LoadExt_GREMEDY_string_marker()
{
	int numFailed = 0;
	_funcptr_glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)IntGetProcAddress("glStringMarkerGREMEDY");
	if(!_funcptr_glStringMarkerGREMEDY) ++numFailed;
	return numFailed;
}