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
struct TYPE_3__ {int /*<<< orphan*/  conv_idx; int /*<<< orphan*/  conv_buf; int /*<<< orphan*/  cepstrum_buf; int /*<<< orphan*/  kernel_buf; int /*<<< orphan*/  kernel_tmp_buf; int /*<<< orphan*/  dump_buf; int /*<<< orphan*/  analysis_buf; int /*<<< orphan*/ * cepstrum_irdft; int /*<<< orphan*/ * cepstrum_rdft; int /*<<< orphan*/ * fft_ctx; int /*<<< orphan*/ * irdft; int /*<<< orphan*/ * rdft; int /*<<< orphan*/ * analysis_irdft; int /*<<< orphan*/ * analysis_rdft; } ;
typedef  TYPE_1__ FIREqualizerContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_rdft_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void common_uninit(FIREqualizerContext *s)
{
    av_rdft_end(s->analysis_rdft);
    av_rdft_end(s->analysis_irdft);
    av_rdft_end(s->rdft);
    av_rdft_end(s->irdft);
    av_fft_end(s->fft_ctx);
    av_rdft_end(s->cepstrum_rdft);
    av_rdft_end(s->cepstrum_irdft);
    s->analysis_rdft = s->analysis_irdft = s->rdft = s->irdft = NULL;
    s->fft_ctx = NULL;
    s->cepstrum_rdft = NULL;
    s->cepstrum_irdft = NULL;

    av_freep(&s->analysis_buf);
    av_freep(&s->dump_buf);
    av_freep(&s->kernel_tmp_buf);
    av_freep(&s->kernel_buf);
    av_freep(&s->cepstrum_buf);
    av_freep(&s->conv_buf);
    av_freep(&s->conv_idx);
}