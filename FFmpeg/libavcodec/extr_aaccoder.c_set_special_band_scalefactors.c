#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_windows; int num_swb; scalar_t__* group_len; } ;
struct TYPE_5__ {scalar_t__* band_type; int* sf_idx; scalar_t__* zeroes; TYPE_1__ ics; int /*<<< orphan*/ * pns_ener; int /*<<< orphan*/ * is_ener; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  int /*<<< orphan*/  AACEncContext ;

/* Variables and functions */
 scalar_t__ INTENSITY_BT ; 
 scalar_t__ INTENSITY_BT2 ; 
 scalar_t__ NOISE_BT ; 
 int SCALE_MAX_DIFF ; 
 void* av_clip (int,int,int) ; 
 int ceilf (int) ; 
 int log2f (int /*<<< orphan*/ ) ; 
 int roundf (int) ; 

__attribute__((used)) static void set_special_band_scalefactors(AACEncContext *s, SingleChannelElement *sce)
{
    int w, g;
    int prevscaler_n = -255, prevscaler_i = 0;
    int bands = 0;

    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
        for (g = 0; g < sce->ics.num_swb; g++) {
            if (sce->zeroes[w*16+g])
                continue;
            if (sce->band_type[w*16+g] == INTENSITY_BT || sce->band_type[w*16+g] == INTENSITY_BT2) {
                sce->sf_idx[w*16+g] = av_clip(roundf(log2f(sce->is_ener[w*16+g])*2), -155, 100);
                bands++;
            } else if (sce->band_type[w*16+g] == NOISE_BT) {
                sce->sf_idx[w*16+g] = av_clip(3+ceilf(log2f(sce->pns_ener[w*16+g])*2), -100, 155);
                if (prevscaler_n == -255)
                    prevscaler_n = sce->sf_idx[w*16+g];
                bands++;
            }
        }
    }

    if (!bands)
        return;

    /* Clip the scalefactor indices */
    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
        for (g = 0; g < sce->ics.num_swb; g++) {
            if (sce->zeroes[w*16+g])
                continue;
            if (sce->band_type[w*16+g] == INTENSITY_BT || sce->band_type[w*16+g] == INTENSITY_BT2) {
                sce->sf_idx[w*16+g] = prevscaler_i = av_clip(sce->sf_idx[w*16+g], prevscaler_i - SCALE_MAX_DIFF, prevscaler_i + SCALE_MAX_DIFF);
            } else if (sce->band_type[w*16+g] == NOISE_BT) {
                sce->sf_idx[w*16+g] = prevscaler_n = av_clip(sce->sf_idx[w*16+g], prevscaler_n - SCALE_MAX_DIFF, prevscaler_n + SCALE_MAX_DIFF);
            }
        }
    }
}