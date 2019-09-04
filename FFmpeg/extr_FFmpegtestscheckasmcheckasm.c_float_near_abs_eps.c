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
 float fabsf (float) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,float,float,float,float) ; 
 int /*<<< orphan*/  stderr ; 

int float_near_abs_eps(float a, float b, float eps)
{
    float abs_diff = fabsf(a - b);
    if (abs_diff < eps)
        return 1;

    fprintf(stderr, "test failed comparing %g with %g (abs diff=%g with EPS=%g)\n", a, b, abs_diff, eps);

    return 0;
}