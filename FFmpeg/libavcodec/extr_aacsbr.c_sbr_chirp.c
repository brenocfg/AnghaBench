#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int** bs_invf_mode; float* bw_array; } ;
struct TYPE_5__ {int n_q; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;

/* Variables and functions */

__attribute__((used)) static void sbr_chirp(SpectralBandReplication *sbr, SBRData *ch_data)
{
    int i;
    float new_bw;
    static const float bw_tab[] = { 0.0f, 0.75f, 0.9f, 0.98f };

    for (i = 0; i < sbr->n_q; i++) {
        if (ch_data->bs_invf_mode[0][i] + ch_data->bs_invf_mode[1][i] == 1) {
            new_bw = 0.6f;
        } else
            new_bw = bw_tab[ch_data->bs_invf_mode[0][i]];

        if (new_bw < ch_data->bw_array[i]) {
            new_bw = 0.75f    * new_bw + 0.25f    * ch_data->bw_array[i];
        } else
            new_bw = 0.90625f * new_bw + 0.09375f * ch_data->bw_array[i];
        ch_data->bw_array[i] = new_bw < 0.015625f ? 0.0f : new_bw;
    }
}