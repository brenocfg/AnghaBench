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
typedef  int int16_t ;

/* Variables and functions */

void ff_vp8_luma_dc_wht_dc_mmi(int16_t block[4][4][16], int16_t dc[16])
{
    int val = (dc[0] + 3) >> 3;

    dc[0] = 0;

    block[0][0][0] = val;
    block[0][1][0] = val;
    block[0][2][0] = val;
    block[0][3][0] = val;
    block[1][0][0] = val;
    block[1][1][0] = val;
    block[1][2][0] = val;
    block[1][3][0] = val;
    block[2][0][0] = val;
    block[2][1][0] = val;
    block[2][2][0] = val;
    block[2][3][0] = val;
    block[3][0][0] = val;
    block[3][1][0] = val;
    block[3][2][0] = val;
    block[3][3][0] = val;
}