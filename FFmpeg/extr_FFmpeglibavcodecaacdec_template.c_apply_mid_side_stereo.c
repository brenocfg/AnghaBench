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
struct TYPE_12__ {TYPE_2__* fdsp; } ;
struct TYPE_11__ {TYPE_1__* ch; scalar_t__* ms_mask; } ;
struct TYPE_10__ {int* swb_offset; int num_window_groups; int max_sfb; int* group_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* butterflies_float ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ;} ;
struct TYPE_8__ {scalar_t__* band_type; int /*<<< orphan*/ * coeffs; TYPE_3__ ics; } ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_4__ ChannelElement ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 scalar_t__ NOISE_BT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void apply_mid_side_stereo(AACContext *ac, ChannelElement *cpe)
{
    const IndividualChannelStream *ics = &cpe->ch[0].ics;
    INTFLOAT *ch0 = cpe->ch[0].coeffs;
    INTFLOAT *ch1 = cpe->ch[1].coeffs;
    int g, i, group, idx = 0;
    const uint16_t *offsets = ics->swb_offset;
    for (g = 0; g < ics->num_window_groups; g++) {
        for (i = 0; i < ics->max_sfb; i++, idx++) {
            if (cpe->ms_mask[idx] &&
                cpe->ch[0].band_type[idx] < NOISE_BT &&
                cpe->ch[1].band_type[idx] < NOISE_BT) {
#if USE_FIXED
                for (group = 0; group < ics->group_len[g]; group++) {
                    ac->fdsp->butterflies_fixed(ch0 + group * 128 + offsets[i],
                                                ch1 + group * 128 + offsets[i],
                                                offsets[i+1] - offsets[i]);
#else
                for (group = 0; group < ics->group_len[g]; group++) {
                    ac->fdsp->butterflies_float(ch0 + group * 128 + offsets[i],
                                               ch1 + group * 128 + offsets[i],
                                               offsets[i+1] - offsets[i]);
#endif /* USE_FIXED */
                }
            }
        }
        ch0 += ics->group_len[g] * 128;
        ch1 += ics->group_len[g] * 128;
    }
}