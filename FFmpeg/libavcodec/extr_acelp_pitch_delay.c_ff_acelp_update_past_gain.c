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
 int FFMAX (int,int) ; 
 int ff_log2_q15 (int) ; 

void ff_acelp_update_past_gain(
    int16_t* quant_energy,
    int gain_corr_factor,
    int log2_ma_pred_order,
    int erasure)
{
    int i;
    int avg_gain=quant_energy[(1 << log2_ma_pred_order) - 1]; // (5.10)

    for(i=(1 << log2_ma_pred_order) - 1; i>0; i--)
    {
        avg_gain       += quant_energy[i-1];
        quant_energy[i] = quant_energy[i-1];
    }

    if(erasure)
        quant_energy[0] = FFMAX(avg_gain >> log2_ma_pred_order, -10240) - 4096; // -10 and -4 in (5.10)
    else
        quant_energy[0] = (6165 * ((ff_log2_q15(gain_corr_factor) >> 2) - (13 << 13))) >> 13;
}