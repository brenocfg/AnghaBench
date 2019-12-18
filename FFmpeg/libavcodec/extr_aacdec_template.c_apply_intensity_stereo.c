#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_12__ {TYPE_1__* fdsp; int /*<<< orphan*/  avctx; int /*<<< orphan*/  (* subband_scale ) (int*,int*,int,int,int const,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int* ms_mask; TYPE_2__* ch; } ;
struct TYPE_10__ {int* swb_offset; int num_window_groups; int max_sfb; int* group_len; } ;
struct TYPE_9__ {int* coeffs; int* band_type; int* band_type_run_end; int* sf; TYPE_3__ ics; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* vector_fmul_scalar ) (int*,int*,int,int const) ;} ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int INTFLOAT ;
typedef  TYPE_4__ ChannelElement ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 int INTENSITY_BT ; 
 int INTENSITY_BT2 ; 
 int /*<<< orphan*/  stub1 (int*,int*,int,int,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int,int const) ; 

__attribute__((used)) static void apply_intensity_stereo(AACContext *ac,
                                   ChannelElement *cpe, int ms_present)
{
    const IndividualChannelStream *ics = &cpe->ch[1].ics;
    SingleChannelElement         *sce1 = &cpe->ch[1];
    INTFLOAT *coef0 = cpe->ch[0].coeffs, *coef1 = cpe->ch[1].coeffs;
    const uint16_t *offsets = ics->swb_offset;
    int g, group, i, idx = 0;
    int c;
    INTFLOAT scale;
    for (g = 0; g < ics->num_window_groups; g++) {
        for (i = 0; i < ics->max_sfb;) {
            if (sce1->band_type[idx] == INTENSITY_BT ||
                sce1->band_type[idx] == INTENSITY_BT2) {
                const int bt_run_end = sce1->band_type_run_end[idx];
                for (; i < bt_run_end; i++, idx++) {
                    c = -1 + 2 * (sce1->band_type[idx] - 14);
                    if (ms_present)
                        c *= 1 - 2 * cpe->ms_mask[idx];
                    scale = c * sce1->sf[idx];
                    for (group = 0; group < ics->group_len[g]; group++)
#if USE_FIXED
                        ac->subband_scale(coef1 + group * 128 + offsets[i],
                                      coef0 + group * 128 + offsets[i],
                                      scale,
                                      23,
                                      offsets[i + 1] - offsets[i] ,ac->avctx);
#else
                        ac->fdsp->vector_fmul_scalar(coef1 + group * 128 + offsets[i],
                                                    coef0 + group * 128 + offsets[i],
                                                    scale,
                                                    offsets[i + 1] - offsets[i]);
#endif /* USE_FIXED */
                }
            } else {
                int bt_run_end = sce1->band_type_run_end[idx];
                idx += bt_run_end - i;
                i    = bt_run_end;
            }
        }
        coef0 += ics->group_len[g] * 128;
        coef1 += ics->group_len[g] * 128;
    }
}