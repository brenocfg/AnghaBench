#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_5__ {size_t** diff_peak_cb; size_t** scale_factor; int /*<<< orphan*/ * cb_to_level; int /*<<< orphan*/ ** quantized; scalar_t__** adpcm_history; int /*<<< orphan*/ ** subband; int /*<<< orphan*/ ** quant; int /*<<< orphan*/ ** prediction_mode; int /*<<< orphan*/ ** abits; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  SUBBAND_SAMPLES ; 
 size_t calc_one_scale (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_dca_scale_factor_quant7 ; 
 int /*<<< orphan*/  ff_dcaadpcm_do_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t get_step_size (TYPE_1__*,int,int) ; 

__attribute__((used)) static inline void quantize_adpcm_subband(DCAEncContext *c, int ch, int band)
{
    int32_t step_size;
    int32_t diff_peak_cb = c->diff_peak_cb[ch][band];
    c->scale_factor[ch][band] = calc_one_scale(c, diff_peak_cb,
                                               c->abits[ch][band],
                                               &c->quant[ch][band]);

    step_size = get_step_size(c, ch, band);
    ff_dcaadpcm_do_real(c->prediction_mode[ch][band],
                        c->quant[ch][band],
                        ff_dca_scale_factor_quant7[c->scale_factor[ch][band]],
                        step_size, c->adpcm_history[ch][band], c->subband[ch][band],
                        c->adpcm_history[ch][band] + 4, c->quantized[ch][band],
                        SUBBAND_SAMPLES, c->cb_to_level[-diff_peak_cb]);
}