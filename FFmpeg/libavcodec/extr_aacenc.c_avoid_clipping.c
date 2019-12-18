#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float clip_avoidance_factor; int num_windows; int max_sfb; int* swb_sizes; } ;
struct TYPE_5__ {float* coeffs; TYPE_1__ ics; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  int /*<<< orphan*/  AACEncContext ;

/* Variables and functions */

__attribute__((used)) static void avoid_clipping(AACEncContext *s, SingleChannelElement *sce)
{
    int start, i, j, w;

    if (sce->ics.clip_avoidance_factor < 1.0f) {
        for (w = 0; w < sce->ics.num_windows; w++) {
            start = 0;
            for (i = 0; i < sce->ics.max_sfb; i++) {
                float *swb_coeffs = &sce->coeffs[start + w*128];
                for (j = 0; j < sce->ics.swb_sizes[i]; j++)
                    swb_coeffs[j] *= sce->ics.clip_avoidance_factor;
                start += sce->ics.swb_sizes[i];
            }
        }
    }
}