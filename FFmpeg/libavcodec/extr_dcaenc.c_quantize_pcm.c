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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int fullband_channels; int** prediction_mode; int /*<<< orphan*/ *** quantized; int /*<<< orphan*/ ** quant; int /*<<< orphan*/ *** subband; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int SUBBAND_SAMPLES ; 
 int /*<<< orphan*/  quantize_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void quantize_pcm(DCAEncContext *c)
{
    int sample, band, ch;

    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++) {
            if (c->prediction_mode[ch][band] == -1) {
                for (sample = 0; sample < SUBBAND_SAMPLES; sample++) {
                    int32_t val = quantize_value(c->subband[ch][band][sample],
                                                 c->quant[ch][band]);
                    c->quantized[ch][band][sample] = val;
                }
            }
        }
    }
}