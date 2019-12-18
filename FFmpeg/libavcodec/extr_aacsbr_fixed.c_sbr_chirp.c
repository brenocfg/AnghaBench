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
typedef  int int64_t ;
struct TYPE_6__ {int** bs_invf_mode; int* bw_array; } ;
struct TYPE_5__ {int n_q; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;

/* Variables and functions */

__attribute__((used)) static void sbr_chirp(SpectralBandReplication *sbr, SBRData *ch_data)
{
    int i;
    int new_bw;
    static const int bw_tab[] = { 0, 1610612736, 1932735283, 2104533975 };
    int64_t accu;

    for (i = 0; i < sbr->n_q; i++) {
        if (ch_data->bs_invf_mode[0][i] + ch_data->bs_invf_mode[1][i] == 1)
            new_bw = 1288490189;
        else
            new_bw = bw_tab[ch_data->bs_invf_mode[0][i]];

        if (new_bw < ch_data->bw_array[i]){
            accu  = (int64_t)new_bw * 1610612736;
            accu += (int64_t)ch_data->bw_array[i] * 0x20000000;
            new_bw = (int)((accu + 0x40000000) >> 31);
        } else {
            accu  = (int64_t)new_bw * 1946157056;
            accu += (int64_t)ch_data->bw_array[i] * 201326592;
            new_bw = (int)((accu + 0x40000000) >> 31);
        }
        ch_data->bw_array[i] = new_bw < 0x2000000 ? 0 : new_bw;
    }
}