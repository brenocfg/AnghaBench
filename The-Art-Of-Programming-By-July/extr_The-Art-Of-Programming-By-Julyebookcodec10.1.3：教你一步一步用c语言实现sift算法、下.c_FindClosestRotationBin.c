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

/* Variables and functions */
 float CV_PI ; 

int FindClosestRotationBin (int binCount, float angle)  
{  
	angle += CV_PI;  
	angle /= 2.0 * CV_PI;  
	// calculate the aligned bin  
	angle *= binCount;  
	int idx = (int) angle;  
	if (idx == binCount)  
		idx = 0;  
	return (idx);  
}