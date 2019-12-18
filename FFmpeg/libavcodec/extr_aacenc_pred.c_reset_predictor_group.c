#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * predictor_state; } ;
typedef  TYPE_1__ SingleChannelElement ;
typedef  int /*<<< orphan*/  PredictorState ;

/* Variables and functions */
 int MAX_PREDICTORS ; 
 int /*<<< orphan*/  reset_predict_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void reset_predictor_group(SingleChannelElement *sce, int group_num)
{
    int i;
    PredictorState *ps = sce->predictor_state;
    for (i = group_num - 1; i < MAX_PREDICTORS; i += 30)
        reset_predict_state(&ps[i]);
}