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
uv_to_xy(double   const u,
         double   const v,
         double * const xc,
         double * const yc)
{
/*
    Given 1970 coordinates u, v, determine 1931 chromaticities x, y
*/
    *xc = 3*u / (2*u - 8*v + 4);
    *yc = 2*v / (2*u - 8*v + 4);
}