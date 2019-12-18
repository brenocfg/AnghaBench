#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* mdct_calcw ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/ * mdct_coef; int /*<<< orphan*/ * coeff_shift; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* apply_window_int16 ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int channels; int num_blocks; int /*<<< orphan*/  windowed_samples; TYPE_5__ mdct; scalar_t__ fixed_point; int /*<<< orphan*/  mdct_window; TYPE_2__ ac3dsp; TYPE_1__* fdsp; int /*<<< orphan*/ ** planar_samples; TYPE_4__* blocks; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* vector_fmul ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  SampleType ;
typedef  TYPE_3__ AC3EncodeContext ;
typedef  TYPE_4__ AC3Block ;

/* Variables and functions */
 int AC3_BLOCK_SIZE ; 
 int /*<<< orphan*/  AC3_WINDOW_SIZE ; 
 int /*<<< orphan*/  normalize_samples (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_mdct(AC3EncodeContext *s)
{
    int blk, ch;

    for (ch = 0; ch < s->channels; ch++) {
        for (blk = 0; blk < s->num_blocks; blk++) {
            AC3Block *block = &s->blocks[blk];
            const SampleType *input_samples = &s->planar_samples[ch][blk * AC3_BLOCK_SIZE];

#if CONFIG_AC3ENC_FLOAT
            s->fdsp->vector_fmul(s->windowed_samples, input_samples,
                                s->mdct_window, AC3_WINDOW_SIZE);
#else
            s->ac3dsp.apply_window_int16(s->windowed_samples, input_samples,
                                         s->mdct_window, AC3_WINDOW_SIZE);

            if (s->fixed_point)
                block->coeff_shift[ch+1] = normalize_samples(s);
#endif

            s->mdct.mdct_calcw(&s->mdct, block->mdct_coef[ch+1],
                               s->windowed_samples);
        }
    }
}