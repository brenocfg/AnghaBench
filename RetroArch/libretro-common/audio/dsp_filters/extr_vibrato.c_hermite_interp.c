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

float hermite_interp(float x, float *y)
{
	float c0, c1, c2, c3;
	c0 = y[1];
	c1 = (1.0 / 2.0)*(y[2] - y[0]);
	c2 = (y[0] - (5.0 / 2.0)*y[1]) + (2.0*y[2] - (1.0 / 2.0)*y[3]);
	c3 = (1.0 / 2.0)*(y[3] - y[0]) + (3.0 / 2.0)*(y[1] - y[2]);
	return ((c3*x + c2)*x + c1)*x + c0;
}