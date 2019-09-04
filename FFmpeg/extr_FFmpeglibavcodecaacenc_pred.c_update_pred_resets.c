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
struct TYPE_6__ {int predictor_reset_group; int* predictor_reset_count; } ;
struct TYPE_5__ {TYPE_2__ ics; } ;
typedef  TYPE_1__ SingleChannelElement ;
typedef  TYPE_2__ IndividualChannelStream ;

/* Variables and functions */
 int PRED_RESET_MIN ; 
 int update_counters (TYPE_2__*,int) ; 

__attribute__((used)) static void update_pred_resets(SingleChannelElement *sce)
{
    int i, max_group_id_c, max_frame = 0;
    float avg_frame = 0.0f;
    IndividualChannelStream *ics = &sce->ics;

    /* Update the counters and immediately update any frame behind schedule */
    if ((ics->predictor_reset_group = update_counters(&sce->ics, 1)))
        return;

    for (i = 1; i < 31; i++) {
        /* Count-based */
        if (ics->predictor_reset_count[i] > max_frame) {
            max_group_id_c = i;
            max_frame = ics->predictor_reset_count[i];
        }
        avg_frame = (ics->predictor_reset_count[i] + avg_frame)/2;
    }

    if (max_frame > PRED_RESET_MIN) {
        ics->predictor_reset_group = max_group_id_c;
    } else {
        ics->predictor_reset_group = 0;
    }
}