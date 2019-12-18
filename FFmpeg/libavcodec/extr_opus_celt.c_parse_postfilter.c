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
struct TYPE_5__ {float* pf_gains_new; int /*<<< orphan*/  pf_period_new; } ;
struct TYPE_4__ {scalar_t__ start_band; int framebits; TYPE_2__* block; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ CeltBlock ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_POSTFILTER_MINPERIOD ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_celt_model_tapset ; 
 float** ff_celt_postfilter_taps ; 
 int ff_opus_rc_dec_cdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_opus_rc_dec_log (int /*<<< orphan*/ *,int) ; 
 int ff_opus_rc_dec_uint (int /*<<< orphan*/ *,int) ; 
 int ff_opus_rc_get_raw (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int opus_rc_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_postfilter(CeltFrame *f, OpusRangeCoder *rc, int consumed)
{
    int i;

    memset(f->block[0].pf_gains_new, 0, sizeof(f->block[0].pf_gains_new));
    memset(f->block[1].pf_gains_new, 0, sizeof(f->block[1].pf_gains_new));

    if (f->start_band == 0 && consumed + 16 <= f->framebits) {
        int has_postfilter = ff_opus_rc_dec_log(rc, 1);
        if (has_postfilter) {
            float gain;
            int tapset, octave, period;

            octave = ff_opus_rc_dec_uint(rc, 6);
            period = (16 << octave) + ff_opus_rc_get_raw(rc, 4 + octave) - 1;
            gain   = 0.09375f * (ff_opus_rc_get_raw(rc, 3) + 1);
            tapset = (opus_rc_tell(rc) + 2 <= f->framebits) ?
                     ff_opus_rc_dec_cdf(rc, ff_celt_model_tapset) : 0;

            for (i = 0; i < 2; i++) {
                CeltBlock *block = &f->block[i];

                block->pf_period_new = FFMAX(period, CELT_POSTFILTER_MINPERIOD);
                block->pf_gains_new[0] = gain * ff_celt_postfilter_taps[tapset][0];
                block->pf_gains_new[1] = gain * ff_celt_postfilter_taps[tapset][1];
                block->pf_gains_new[2] = gain * ff_celt_postfilter_taps[tapset][2];
            }
        }

        consumed = opus_rc_tell(rc);
    }

    return consumed;
}