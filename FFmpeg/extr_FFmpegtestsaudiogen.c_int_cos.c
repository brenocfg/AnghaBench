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
 int CSHIFT ; 
 int FRAC_BITS ; 
 int FRAC_ONE ; 
 unsigned short* cos_table ; 

__attribute__((used)) static int int_cos(int a)
{
    int neg, v, f;
    const unsigned short *p;

    a = a & (FRAC_ONE - 1); /* modulo 2 * pi */
    if (a >= (FRAC_ONE / 2))
        a = FRAC_ONE - a;
    neg = 0;
    if (a > (FRAC_ONE / 4)) {
        neg = -1;
        a   = (FRAC_ONE / 2) - a;
    }
    p = cos_table + (a >> CSHIFT);
    /* linear interpolation */
    f = a & ((1 << CSHIFT) - 1);
    v = p[0] + (((p[1] - p[0]) * f + (1 << (CSHIFT - 1))) >> CSHIFT);
    v = (v ^ neg) - neg;
    v = v << (FRAC_BITS - 15);
    return v;
}