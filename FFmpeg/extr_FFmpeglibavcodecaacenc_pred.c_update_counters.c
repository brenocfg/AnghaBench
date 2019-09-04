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
struct TYPE_3__ {scalar_t__* predictor_reset_count; } ;
typedef  TYPE_1__ IndividualChannelStream ;

/* Variables and functions */
 scalar_t__ PRED_RESET_FRAME_MIN ; 

__attribute__((used)) static inline int update_counters(IndividualChannelStream *ics, int inc)
{
    int i;
    for (i = 1; i < 31; i++) {
        ics->predictor_reset_count[i] += inc;
        if (ics->predictor_reset_count[i] > PRED_RESET_FRAME_MIN)
            return i; /* Reset this immediately */
    }
    return 0;
}