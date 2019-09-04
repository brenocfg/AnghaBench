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
 double atan (double) ; 

__attribute__((used)) static double freq2bark(double x)
{
    double d = x / 7500.0;

    return 13.0 * atan(7.6E-4 * x) + 3.5 * atan(d * d);
}