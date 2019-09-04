#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_4__ {int channels; int** prediction_mode; int*** adpcm_history; size_t** scale_factor; scalar_t__** quantized; int /*<<< orphan*/ ** subband; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_COPY128U (int*,int*) ; 
 int /*<<< orphan*/  DCA_ADPCM_COEFFS ; 
 int /*<<< orphan*/  ff_dca_core_dequantize (int*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ff_dca_scale_factor_quant7 ; 
 int get_step_size (TYPE_1__*,int,int) ; 

__attribute__((used)) static void fill_in_adpcm_bufer(DCAEncContext *c)
{
     int ch, band;
     int32_t step_size;
     /* We fill in ADPCM work buffer for subbands which hasn't been ADPCM coded
      * in current frame - we need this data if subband of next frame is
      * ADPCM
      */
     for (ch = 0; ch < c->channels; ch++) {
        for (band = 0; band < 32; band++) {
            int32_t *samples = c->subband[ch][band] - DCA_ADPCM_COEFFS;
            if (c->prediction_mode[ch][band] == -1) {
                step_size = get_step_size(c, ch, band);

                ff_dca_core_dequantize(c->adpcm_history[ch][band],
                                       c->quantized[ch][band]+12, step_size,
                                       ff_dca_scale_factor_quant7[c->scale_factor[ch][band]], 0, 4);
            } else {
                AV_COPY128U(c->adpcm_history[ch][band], c->adpcm_history[ch][band]+4);
            }
            /* Copy dequantized values for LPC analysis.
             * It reduces artifacts in case of extreme quantization,
             * example: in current frame abits is 1 and has no prediction flag,
             * but end of this frame is sine like signal. In this case, if LPC analysis uses
             * original values, likely LPC analysis returns good prediction gain, and sets prediction flag.
             * But there are no proper value in decoder history, so likely result will be no good.
             * Bitstream has "Predictor history flag switch", but this flag disables history for all subbands
             */
            samples[0] = c->adpcm_history[ch][band][0] << 7;
            samples[1] = c->adpcm_history[ch][band][1] << 7;
            samples[2] = c->adpcm_history[ch][band][2] << 7;
            samples[3] = c->adpcm_history[ch][band][3] << 7;
        }
     }
}