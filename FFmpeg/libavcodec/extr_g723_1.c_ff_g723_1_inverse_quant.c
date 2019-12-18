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
typedef  size_t uint8_t ;
typedef  int int16_t ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int LPC_ORDER ; 
 int* dc_lsp ; 
 int** lsp_band0 ; 
 int** lsp_band1 ; 
 int** lsp_band2 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void ff_g723_1_inverse_quant(int16_t *cur_lsp, int16_t *prev_lsp,
                             uint8_t *lsp_index, int bad_frame)
{
    int min_dist, pred;
    int i, j, temp, stable;

    /* Check for frame erasure */
    if (!bad_frame) {
        min_dist     = 0x100;
        pred         = 12288;
    } else {
        min_dist     = 0x200;
        pred         = 23552;
        lsp_index[0] = lsp_index[1] = lsp_index[2] = 0;
    }

    /* Get the VQ table entry corresponding to the transmitted index */
    cur_lsp[0] = lsp_band0[lsp_index[0]][0];
    cur_lsp[1] = lsp_band0[lsp_index[0]][1];
    cur_lsp[2] = lsp_band0[lsp_index[0]][2];
    cur_lsp[3] = lsp_band1[lsp_index[1]][0];
    cur_lsp[4] = lsp_band1[lsp_index[1]][1];
    cur_lsp[5] = lsp_band1[lsp_index[1]][2];
    cur_lsp[6] = lsp_band2[lsp_index[2]][0];
    cur_lsp[7] = lsp_band2[lsp_index[2]][1];
    cur_lsp[8] = lsp_band2[lsp_index[2]][2];
    cur_lsp[9] = lsp_band2[lsp_index[2]][3];

    /* Add predicted vector & DC component to the previously quantized vector */
    for (i = 0; i < LPC_ORDER; i++) {
        temp        = ((prev_lsp[i] - dc_lsp[i]) * pred + (1 << 14)) >> 15;
        cur_lsp[i] += dc_lsp[i] + temp;
    }

    for (i = 0; i < LPC_ORDER; i++) {
        cur_lsp[0]             = FFMAX(cur_lsp[0],  0x180);
        cur_lsp[LPC_ORDER - 1] = FFMIN(cur_lsp[LPC_ORDER - 1], 0x7e00);

        /* Stability check */
        for (j = 1; j < LPC_ORDER; j++) {
            temp = min_dist + cur_lsp[j - 1] - cur_lsp[j];
            if (temp > 0) {
                temp >>= 1;
                cur_lsp[j - 1] -= temp;
                cur_lsp[j]     += temp;
            }
        }
        stable = 1;
        for (j = 1; j < LPC_ORDER; j++) {
            temp = cur_lsp[j - 1] + min_dist - cur_lsp[j] - 4;
            if (temp > 0) {
                stable = 0;
                break;
            }
        }
        if (stable)
            break;
    }
    if (!stable)
        memcpy(cur_lsp, prev_lsp, LPC_ORDER * sizeof(*cur_lsp));
}