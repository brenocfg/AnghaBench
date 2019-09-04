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
 double max (double,double) ; 
 double min (double,double) ; 

double maxProductSubstring(double *a, int length)
{
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxResult = a[0];
	// {-3,-0.5,-10}
	for (int i = 1; i < length; ++i)
	{
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1, end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxResult = max(maxResult, maxEnd);
	}
	return maxResult;
}