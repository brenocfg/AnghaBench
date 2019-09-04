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

__attribute__((used)) static double
weighted_scale_factor(double scale)
{
	// 0 to 1 increasing quickly from 0. This weights smaller blkdiffs higher to add a type of minimum latency
	// I would like to use log(10) / 2.0 + 1, but using different approximation due to no math library
	// y = (x-1)^3 + 1
	double x_m1 = scale - 1;
	return x_m1 * x_m1 * x_m1 + 1;
}