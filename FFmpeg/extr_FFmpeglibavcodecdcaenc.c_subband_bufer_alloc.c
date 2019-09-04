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
struct TYPE_3__ {int /*<<< orphan*/ *** subband; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int DCAENC_SUBBANDS ; 
 int DCA_ADPCM_COEFFS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_CHANNELS ; 
 int SUBBAND_SAMPLES ; 
 int /*<<< orphan*/ * av_calloc (int,int) ; 

__attribute__((used)) static int subband_bufer_alloc(DCAEncContext *c)
{
    int ch, band;
    int32_t *bufer = av_calloc(MAX_CHANNELS * DCAENC_SUBBANDS *
                               (SUBBAND_SAMPLES + DCA_ADPCM_COEFFS),
                               sizeof(int32_t));
    if (!bufer)
        return AVERROR(ENOMEM);

    /* we need a place for DCA_ADPCM_COEFF samples from previous frame
     * to calc prediction coefficients for each subband */
    for (ch = 0; ch < MAX_CHANNELS; ch++) {
        for (band = 0; band < DCAENC_SUBBANDS; band++) {
            c->subband[ch][band] = bufer +
                                   ch * DCAENC_SUBBANDS * (SUBBAND_SAMPLES + DCA_ADPCM_COEFFS) +
                                   band * (SUBBAND_SAMPLES + DCA_ADPCM_COEFFS) + DCA_ADPCM_COEFFS;
        }
    }
    return 0;
}