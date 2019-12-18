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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** sb_samples; int /*<<< orphan*/ * synth_buf_offset; int /*<<< orphan*/ * synth_buf; int /*<<< orphan*/  mpadsp; } ;
typedef  TYPE_1__ MPCContext ;

/* Variables and functions */
 int SAMPLES_PER_BAND ; 
 int /*<<< orphan*/  ff_mpa_synth_filter_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpa_synth_window_fixed ; 

__attribute__((used)) static void mpc_synth(MPCContext *c, int16_t **out, int channels)
{
    int dither_state = 0;
    int i, ch;

    for(ch = 0;  ch < channels; ch++){
        for(i = 0; i < SAMPLES_PER_BAND; i++) {
            ff_mpa_synth_filter_fixed(&c->mpadsp,
                                c->synth_buf[ch], &(c->synth_buf_offset[ch]),
                                ff_mpa_synth_window_fixed, &dither_state,
                                out[ch] + 32 * i, 1,
                                c->sb_samples[ch][i]);
        }
    }
}