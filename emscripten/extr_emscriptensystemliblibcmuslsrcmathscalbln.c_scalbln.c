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
 long INT_MAX ; 
 long INT_MIN ; 
 double scalbn (double,long) ; 

double scalbln(double x, long n)
{
	if (n > INT_MAX)
		n = INT_MAX;
	else if (n < INT_MIN)
		n = INT_MIN;
	return scalbn(x, n);
}