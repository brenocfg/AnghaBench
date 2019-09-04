#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_14__ {int /*<<< orphan*/  is_disabled; TYPE_3__* priv; TYPE_5__** inputs; } ;
struct TYPE_13__ {int /*<<< orphan*/  channel_layout; } ;
struct TYPE_12__ {int channels; int nb_samples; int /*<<< orphan*/ * extended_data; } ;
struct TYPE_11__ {int channels; int block_align; TYPE_1__* cache; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; int /*<<< orphan*/  b2; int /*<<< orphan*/  b1; int /*<<< orphan*/  b0; int /*<<< orphan*/  (* filter ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  clippings; int /*<<< orphan*/  o2; int /*<<< orphan*/  o1; int /*<<< orphan*/  i2; int /*<<< orphan*/  i1; } ;
typedef  TYPE_3__ BiquadsContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int av_channel_layout_extract_channel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_channel(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AVFilterLink *inlink = ctx->inputs[0];
    ThreadData *td = arg;
    AVFrame *buf = td->in;
    AVFrame *out_buf = td->out;
    BiquadsContext *s = ctx->priv;
    const int start = (buf->channels * jobnr) / nb_jobs;
    const int end = (buf->channels * (jobnr+1)) / nb_jobs;
    int ch;

    for (ch = start; ch < end; ch++) {
        if (!((av_channel_layout_extract_channel(inlink->channel_layout, ch) & s->channels))) {
            if (buf != out_buf)
                memcpy(out_buf->extended_data[ch], buf->extended_data[ch],
                       buf->nb_samples * s->block_align);
            continue;
        }

        s->filter(s, buf->extended_data[ch], out_buf->extended_data[ch], buf->nb_samples,
                  &s->cache[ch].i1, &s->cache[ch].i2, &s->cache[ch].o1, &s->cache[ch].o2,
                  s->b0, s->b1, s->b2, s->a1, s->a2, &s->cache[ch].clippings, ctx->is_disabled);
    }

    return 0;
}