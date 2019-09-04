#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct G722Band {int scale_factor; int log_factor; } ;

/* Variables and functions */
 int av_clip (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_adaptive_prediction (struct G722Band*,int) ; 
 int* ff_g722_low_inv_quant4 ; 
 int linear_scale_factor (int) ; 
 scalar_t__* low_log_factor_step ; 

void ff_g722_update_low_predictor(struct G722Band *band, const int ilow)
{
    do_adaptive_prediction(band,
                           band->scale_factor * ff_g722_low_inv_quant4[ilow] >> 10);

    // quantizer adaptation
    band->log_factor   = av_clip((band->log_factor * 127 >> 7) +
                                 low_log_factor_step[ilow], 0, 18432);
    band->scale_factor = linear_scale_factor(band->log_factor - (8 << 11));
}