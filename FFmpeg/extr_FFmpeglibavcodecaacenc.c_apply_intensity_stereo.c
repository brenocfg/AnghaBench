#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ch; scalar_t__* ms_mask; int /*<<< orphan*/ * is_mask; int /*<<< orphan*/  common_window; } ;
struct TYPE_6__ {int num_windows; int* group_len; int num_swb; int* swb_sizes; } ;
struct TYPE_5__ {int* band_type; float* is_ener; int* coeffs; TYPE_2__ ics; } ;
typedef  TYPE_2__ IndividualChannelStream ;
typedef  TYPE_3__ ChannelElement ;

/* Variables and functions */

__attribute__((used)) static void apply_intensity_stereo(ChannelElement *cpe)
{
    int w, w2, g, i;
    IndividualChannelStream *ics = &cpe->ch[0].ics;
    if (!cpe->common_window)
        return;
    for (w = 0; w < ics->num_windows; w += ics->group_len[w]) {
        for (w2 =  0; w2 < ics->group_len[w]; w2++) {
            int start = (w+w2) * 128;
            for (g = 0; g < ics->num_swb; g++) {
                int p  = -1 + 2 * (cpe->ch[1].band_type[w*16+g] - 14);
                float scale = cpe->ch[0].is_ener[w*16+g];
                if (!cpe->is_mask[w*16 + g]) {
                    start += ics->swb_sizes[g];
                    continue;
                }
                if (cpe->ms_mask[w*16 + g])
                    p *= -1;
                for (i = 0; i < ics->swb_sizes[g]; i++) {
                    float sum = (cpe->ch[0].coeffs[start+i] + p*cpe->ch[1].coeffs[start+i])*scale;
                    cpe->ch[0].coeffs[start+i] = sum;
                    cpe->ch[1].coeffs[start+i] = 0.0f;
                }
                start += ics->swb_sizes[g];
            }
        }
    }
}