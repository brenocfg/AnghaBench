#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* out; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_10__ {TYPE_2__* priv; } ;
struct TYPE_9__ {int channels; scalar_t__* extended_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * st; } ;
typedef  TYPE_2__ AudioRNNContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  rnnoise_channel (TYPE_2__*,int /*<<< orphan*/ *,float*,float const*) ; 

__attribute__((used)) static int rnnoise_channels(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AudioRNNContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int start = (out->channels * jobnr) / nb_jobs;
    const int end = (out->channels * (jobnr+1)) / nb_jobs;

    for (int ch = start; ch < end; ch++) {
        rnnoise_channel(s, &s->st[ch],
                        (float *)out->extended_data[ch],
                        (const float *)in->extended_data[ch]);
    }

    return 0;
}