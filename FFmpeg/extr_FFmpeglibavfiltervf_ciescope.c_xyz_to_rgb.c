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
xyz_to_rgb(const double m[3][3],
           double xc, double yc, double zc,
           double * const r, double * const g, double * const b)
{
    *r = m[0][0]*xc + m[0][1]*yc + m[0][2]*zc;
    *g = m[1][0]*xc + m[1][1]*yc + m[1][2]*zc;
    *b = m[2][0]*xc + m[2][1]*yc + m[2][2]*zc;
}