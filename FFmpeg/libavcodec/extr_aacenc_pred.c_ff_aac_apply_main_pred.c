#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t samplerate_index; } ;
struct TYPE_7__ {scalar_t__* window_sequence; int* swb_offset; scalar_t__ predictor_reset_group; scalar_t__* prediction_used; scalar_t__ predictor_present; int /*<<< orphan*/  max_sfb; } ;
struct TYPE_8__ {int /*<<< orphan*/ * predictor_state; TYPE_1__ ics; int /*<<< orphan*/ * prcoeffs; int /*<<< orphan*/ * coeffs; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ AACEncContext ;

/* Variables and functions */
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_aac_pred_sfb_max ; 
 int /*<<< orphan*/  predict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset_all_predictors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_predictor_group (TYPE_2__*,scalar_t__) ; 

void ff_aac_apply_main_pred(AACEncContext *s, SingleChannelElement *sce)
{
    int sfb, k;
    const int pmax = FFMIN(sce->ics.max_sfb, ff_aac_pred_sfb_max[s->samplerate_index]);

    if (sce->ics.window_sequence[0] != EIGHT_SHORT_SEQUENCE) {
        for (sfb = 0; sfb < pmax; sfb++) {
            for (k = sce->ics.swb_offset[sfb]; k < sce->ics.swb_offset[sfb + 1]; k++) {
                predict(&sce->predictor_state[k], &sce->coeffs[k], &sce->prcoeffs[k],
                        sce->ics.predictor_present && sce->ics.prediction_used[sfb]);
            }
        }
        if (sce->ics.predictor_reset_group) {
            reset_predictor_group(sce, sce->ics.predictor_reset_group);
        }
    } else {
        reset_all_predictors(sce->predictor_state);
    }
}