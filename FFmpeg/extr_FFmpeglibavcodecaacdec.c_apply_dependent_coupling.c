#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_19__ {int /*<<< orphan*/  avctx; TYPE_2__* oc; } ;
struct TYPE_15__ {float** gain; } ;
struct TYPE_18__ {TYPE_4__ coup; TYPE_3__* ch; } ;
struct TYPE_17__ {int* swb_offset; int num_window_groups; int max_sfb; int* group_len; } ;
struct TYPE_16__ {float* coeffs; } ;
struct TYPE_14__ {float* coeffs; scalar_t__* band_type; TYPE_6__ ics; } ;
struct TYPE_12__ {scalar_t__ object_type; } ;
struct TYPE_13__ {TYPE_1__ m4ac; } ;
typedef  TYPE_5__ SingleChannelElement ;
typedef  TYPE_6__ IndividualChannelStream ;
typedef  TYPE_7__ ChannelElement ;
typedef  TYPE_8__ AACContext ;

/* Variables and functions */
 scalar_t__ AOT_AAC_LTP ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ ZERO_BT ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void apply_dependent_coupling(AACContext *ac,
                                     SingleChannelElement *target,
                                     ChannelElement *cce, int index)
{
    IndividualChannelStream *ics = &cce->ch[0].ics;
    const uint16_t *offsets = ics->swb_offset;
    float *dest = target->coeffs;
    const float *src = cce->ch[0].coeffs;
    int g, i, group, k, idx = 0;
    if (ac->oc[1].m4ac.object_type == AOT_AAC_LTP) {
        av_log(ac->avctx, AV_LOG_ERROR,
               "Dependent coupling is not supported together with LTP\n");
        return;
    }
    for (g = 0; g < ics->num_window_groups; g++) {
        for (i = 0; i < ics->max_sfb; i++, idx++) {
            if (cce->ch[0].band_type[idx] != ZERO_BT) {
                const float gain = cce->coup.gain[index][idx];
                for (group = 0; group < ics->group_len[g]; group++) {
                    for (k = offsets[i]; k < offsets[i + 1]; k++) {
                        // FIXME: SIMDify
                        dest[group * 128 + k] += gain * src[group * 128 + k];
                    }
                }
            }
        }
        dest += ics->group_len[g] * 128;
        src  += ics->group_len[g] * 128;
    }
}