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

void ff_h264_chroma422_dc_dequant_idct_8_mmi(int16_t *block, int qmul)
{
    int temp[8];
    int t[8];

    temp[0] = block[0] + block[16];
    temp[1] = block[0] - block[16];
    temp[2] = block[32] + block[48];
    temp[3] = block[32] - block[48];
    temp[4] = block[64] + block[80];
    temp[5] = block[64] - block[80];
    temp[6] = block[96] + block[112];
    temp[7] = block[96] - block[112];

    t[0] = temp[0] + temp[4] + temp[2] + temp[6];
    t[1] = temp[0] - temp[4] + temp[2] - temp[6];
    t[2] = temp[0] - temp[4] - temp[2] + temp[6];
    t[3] = temp[0] + temp[4] - temp[2] - temp[6];
    t[4] = temp[1] + temp[5] + temp[3] + temp[7];
    t[5] = temp[1] - temp[5] + temp[3] - temp[7];
    t[6] = temp[1] - temp[5] - temp[3] + temp[7];
    t[7] = temp[1] + temp[5] - temp[3] - temp[7];

    block[  0]= (t[0]*qmul + 128) >> 8;
    block[ 32]= (t[1]*qmul + 128) >> 8;
    block[ 64]= (t[2]*qmul + 128) >> 8;
    block[ 96]= (t[3]*qmul + 128) >> 8;
    block[ 16]= (t[4]*qmul + 128) >> 8;
    block[ 48]= (t[5]*qmul + 128) >> 8;
    block[ 80]= (t[6]*qmul + 128) >> 8;
    block[112]= (t[7]*qmul + 128) >> 8;
}