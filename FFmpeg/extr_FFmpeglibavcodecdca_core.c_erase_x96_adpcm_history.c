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
struct TYPE_3__ {scalar_t__** x96_subband_samples; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ZERO128 (scalar_t__) ; 
 scalar_t__ DCA_ADPCM_COEFFS ; 
 int DCA_CHANNELS ; 
 int DCA_SUBBANDS_X96 ; 
 int /*<<< orphan*/  emms_c () ; 

__attribute__((used)) static void erase_x96_adpcm_history(DCACoreDecoder *s)
{
    int ch, band;

    // Erase ADPCM history from previous frame if
    // predictor history switch was disabled
    for (ch = 0; ch < DCA_CHANNELS; ch++)
        for (band = 0; band < DCA_SUBBANDS_X96; band++)
            AV_ZERO128(s->x96_subband_samples[ch][band] - DCA_ADPCM_COEFFS);

    emms_c();
}