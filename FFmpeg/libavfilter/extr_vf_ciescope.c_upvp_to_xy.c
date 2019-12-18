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
upvp_to_xy(double   const up,
           double   const vp,
           double * const xc,
           double * const yc)
{
/*
    Given 1976 coordinates u', v', determine 1931 chromaticities x, y
*/
    *xc = 9*up / (6*up - 16*vp + 12);
    *yc = 4*vp / (6*up - 16*vp + 12);
}