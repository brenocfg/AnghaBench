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
 int COEFF_0 ; 
 int COEFF_1 ; 
 int COEFF_2 ; 

__attribute__((used)) static void idct6(int pre_mant[6])
{
    int tmp;
    int even0, even1, even2, odd0, odd1, odd2;

    odd1 = pre_mant[1] - pre_mant[3] - pre_mant[5];

    even2 = ( pre_mant[2]                * COEFF_0) >> 23;
    tmp   = ( pre_mant[4]                * COEFF_1) >> 23;
    odd0  = ((pre_mant[1] + pre_mant[5]) * COEFF_2) >> 23;

    even0 = pre_mant[0] + (tmp >> 1);
    even1 = pre_mant[0] - tmp;

    tmp = even0;
    even0 = tmp + even2;
    even2 = tmp - even2;

    tmp = odd0;
    odd0 = tmp + pre_mant[1] + pre_mant[3];
    odd2 = tmp + pre_mant[5] - pre_mant[3];

    pre_mant[0] = even0 + odd0;
    pre_mant[1] = even1 + odd1;
    pre_mant[2] = even2 + odd2;
    pre_mant[3] = even2 - odd2;
    pre_mant[4] = even1 - odd1;
    pre_mant[5] = even0 - odd0;
}