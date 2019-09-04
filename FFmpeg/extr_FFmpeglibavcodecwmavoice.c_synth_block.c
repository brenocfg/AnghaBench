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
struct frame_type_desc {scalar_t__ acb_type; int n_blocks; } ;
struct TYPE_5__ {int lsps; } ;
typedef  TYPE_1__ WMAVoiceContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ ACB_TYPE_NONE ; 
 int MAX_LSPS ; 
 double cos (double const) ; 
 int /*<<< orphan*/  ff_acelp_lspd2lpc (double*,float*,int) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (float*,float*,float*,int,int) ; 
 int /*<<< orphan*/  synth_block_fcb_acb (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,struct frame_type_desc const*,float*) ; 
 int /*<<< orphan*/  synth_block_hardcoded (TYPE_1__*,int /*<<< orphan*/ *,int,int,struct frame_type_desc const*,float*) ; 

__attribute__((used)) static void synth_block(WMAVoiceContext *s, GetBitContext *gb,
                        int block_idx, int size,
                        int block_pitch_sh2,
                        const double *lsps, const double *prev_lsps,
                        const struct frame_type_desc *frame_desc,
                        float *excitation, float *synth)
{
    double i_lsps[MAX_LSPS];
    float lpcs[MAX_LSPS];
    float fac;
    int n;

    if (frame_desc->acb_type == ACB_TYPE_NONE)
        synth_block_hardcoded(s, gb, block_idx, size, frame_desc, excitation);
    else
        synth_block_fcb_acb(s, gb, block_idx, size, block_pitch_sh2,
                            frame_desc, excitation);

    /* convert interpolated LSPs to LPCs */
    fac = (block_idx + 0.5) / frame_desc->n_blocks;
    for (n = 0; n < s->lsps; n++) // LSF -> LSP
        i_lsps[n] = cos(prev_lsps[n] + fac * (lsps[n] - prev_lsps[n]));
    ff_acelp_lspd2lpc(i_lsps, lpcs, s->lsps >> 1);

    /* Speech synthesis */
    ff_celp_lp_synthesis_filterf(synth, lpcs, excitation, size, s->lsps);
}