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

__attribute__((used)) static double brown_filter(double white, double *buf)
{
    double brown;

    brown = ((0.02 * white) + buf[0]) / 1.02;
    buf[0] = brown;
    return brown * 3.5;
}