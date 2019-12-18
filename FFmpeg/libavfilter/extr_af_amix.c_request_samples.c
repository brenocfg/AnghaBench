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
struct TYPE_5__ {int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * inputs; TYPE_1__* priv; } ;
struct TYPE_4__ {int nb_inputs; int* input_state; int /*<<< orphan*/ * fifos; } ;
typedef  TYPE_1__ MixContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int INPUT_EOF ; 
 int INPUT_ON ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_inlink_request_frame (int /*<<< orphan*/ ) ; 
 int output_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_samples(AVFilterContext *ctx, int min_samples)
{
    MixContext *s = ctx->priv;
    int i;

    av_assert0(s->nb_inputs > 1);

    for (i = 1; i < s->nb_inputs; i++) {
        if (!(s->input_state[i] & INPUT_ON) ||
             (s->input_state[i] & INPUT_EOF))
            continue;
        if (av_audio_fifo_size(s->fifos[i]) >= min_samples)
            continue;
        ff_inlink_request_frame(ctx->inputs[i]);
    }
    return output_frame(ctx->outputs[0]);
}