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
struct TYPE_12__ {TYPE_2__* oc; } ;
struct TYPE_10__ {int predictor_initialized; scalar_t__* window_sequence; int* swb_offset; scalar_t__ predictor_reset_group; scalar_t__* prediction_used; scalar_t__ predictor_present; } ;
struct TYPE_11__ {int /*<<< orphan*/ * predictor_state; TYPE_3__ ics; int /*<<< orphan*/ * coeffs; } ;
struct TYPE_8__ {size_t sampling_index; } ;
struct TYPE_9__ {TYPE_1__ m4ac; } ;
typedef  TYPE_4__ SingleChannelElement ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int* ff_aac_pred_sfb_max ; 
 int /*<<< orphan*/  predict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset_all_predictors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_predictor_group (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void apply_prediction(AACContext *ac, SingleChannelElement *sce)
{
    int sfb, k;

    if (!sce->ics.predictor_initialized) {
        reset_all_predictors(sce->predictor_state);
        sce->ics.predictor_initialized = 1;
    }

    if (sce->ics.window_sequence[0] != EIGHT_SHORT_SEQUENCE) {
        for (sfb = 0;
             sfb < ff_aac_pred_sfb_max[ac->oc[1].m4ac.sampling_index];
             sfb++) {
            for (k = sce->ics.swb_offset[sfb];
                 k < sce->ics.swb_offset[sfb + 1];
                 k++) {
                predict(&sce->predictor_state[k], &sce->coeffs[k],
                        sce->ics.predictor_present &&
                        sce->ics.prediction_used[sfb]);
            }
        }
        if (sce->ics.predictor_reset_group)
            reset_predictor_group(sce->predictor_state,
                                  sce->ics.predictor_reset_group);
    } else
        reset_all_predictors(sce->predictor_state);
}