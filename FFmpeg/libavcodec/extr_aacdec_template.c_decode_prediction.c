#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* oc; int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {int predictor_reset_group; scalar_t__* prediction_used; int /*<<< orphan*/  max_sfb; } ;
struct TYPE_7__ {size_t sampling_index; } ;
struct TYPE_8__ {TYPE_1__ m4ac; } ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ff_aac_pred_sfb_max ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_prediction(AACContext *ac, IndividualChannelStream *ics,
                             GetBitContext *gb)
{
    int sfb;
    if (get_bits1(gb)) {
        ics->predictor_reset_group = get_bits(gb, 5);
        if (ics->predictor_reset_group == 0 ||
            ics->predictor_reset_group > 30) {
            av_log(ac->avctx, AV_LOG_ERROR,
                   "Invalid Predictor Reset Group.\n");
            return AVERROR_INVALIDDATA;
        }
    }
    for (sfb = 0; sfb < FFMIN(ics->max_sfb, ff_aac_pred_sfb_max[ac->oc[1].m4ac.sampling_index]); sfb++) {
        ics->prediction_used[sfb] = get_bits1(gb);
    }
    return 0;
}