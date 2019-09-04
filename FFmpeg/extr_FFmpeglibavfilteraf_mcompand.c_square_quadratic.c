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

__attribute__((used)) static void square_quadratic(double const *x, double *y)
{
    y[0] = x[0] * x[0];
    y[1] = 2 * x[0] * x[1];
    y[2] = 2 * x[0] * x[2] + x[1] * x[1];
    y[3] = 2 * x[1] * x[2];
    y[4] = x[2] * x[2];
}