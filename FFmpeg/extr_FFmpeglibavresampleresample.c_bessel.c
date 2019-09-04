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

__attribute__((used)) static double bessel(double x)
{
    double v     = 1;
    double lastv = 0;
    double t     = 1;
    int i;

    x = x * x / 4;
    for (i = 1; v != lastv; i++) {
        lastv = v;
        t    *= x / (i * i);
        v    += t;
    }
    return v;
}