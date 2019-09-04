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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int fullband_channels; int** prediction_mode; int /*<<< orphan*/ ** diff_peak_cb; scalar_t__ consumed_adpcm_bits; int /*<<< orphan*/  adpcm_ctx; int /*<<< orphan*/ ** subband; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_ADPCM_COEFFS ; 
 int SUBBAND_SAMPLES ; 
 int ff_dcaadpcm_subband_analysis (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_peak (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void adpcm_analysis(DCAEncContext *c)
{
    int ch, band;
    int pred_vq_id;
    int32_t *samples;
    int32_t estimated_diff[SUBBAND_SAMPLES];

    c->consumed_adpcm_bits = 0;
    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++) {
            samples = c->subband[ch][band] - DCA_ADPCM_COEFFS;
            pred_vq_id = ff_dcaadpcm_subband_analysis(&c->adpcm_ctx, samples,
                                                      SUBBAND_SAMPLES, estimated_diff);
            if (pred_vq_id >= 0) {
                c->prediction_mode[ch][band] = pred_vq_id;
                c->consumed_adpcm_bits += 12; //12 bits to transmit prediction vq index
                c->diff_peak_cb[ch][band] = find_peak(c, estimated_diff, 16);
            } else {
                c->prediction_mode[ch][band] = -1;
            }
        }
    }
}