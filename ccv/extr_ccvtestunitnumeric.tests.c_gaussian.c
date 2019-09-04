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
 int CCV_PI ; 
 double exp (double) ; 
 double sqrt (int) ; 

double gaussian(double x, double y, void* data)
{
	return exp(-(x * x + y * y) / 20) / sqrt(CCV_PI * 20);
}