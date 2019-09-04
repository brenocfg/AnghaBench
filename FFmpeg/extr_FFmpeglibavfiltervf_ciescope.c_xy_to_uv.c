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

__attribute__((used)) static void
xy_to_uv(double xc,
         double yc,
         double * const u,
         double * const v)
{
/*
    Given 1931 chromaticities x, y, determine 1960 coordinates u, v
*/
    *u = 4*xc / (- 2*xc + 12*yc + 3);
    *v = 6*yc / (- 2*xc + 12*yc + 3);
}