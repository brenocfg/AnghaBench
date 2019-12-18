#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_14__ {int nb_inputs; TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_13__ {int channel_layout; TYPE_4__* src; } ;
struct TYPE_12__ {size_t input; int in_channel; int out_channel; int /*<<< orphan*/  in_channel_idx; } ;
struct TYPE_11__ {int nb_channels; TYPE_2__* channels; } ;
typedef  TYPE_1__ JoinContext ;
typedef  TYPE_2__ ChannelMap ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_channel_layout_extract_channel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_get_channel_layout_channel_index (int,int) ; 
 int av_get_channel_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  guess_map_any (TYPE_4__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  guess_map_matching (TYPE_4__*,TYPE_2__*,int*) ; 

__attribute__((used)) static int join_config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    JoinContext       *s = ctx->priv;
    uint64_t *inputs;   // nth element tracks which channels are used from nth input
    int i, ret = 0;

    /* initialize inputs to user-specified mappings */
    if (!(inputs = av_mallocz_array(ctx->nb_inputs, sizeof(*inputs))))
        return AVERROR(ENOMEM);
    for (i = 0; i < s->nb_channels; i++) {
        ChannelMap *ch = &s->channels[i];
        AVFilterLink *inlink;

        if (ch->input < 0)
            continue;

        inlink = ctx->inputs[ch->input];

        if (!ch->in_channel)
            ch->in_channel = av_channel_layout_extract_channel(inlink->channel_layout,
                                                               ch->in_channel_idx);

        if (!(ch->in_channel & inlink->channel_layout)) {
            av_log(ctx, AV_LOG_ERROR, "Requested channel %s is not present in "
                   "input stream #%d.\n", av_get_channel_name(ch->in_channel),
                   ch->input);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        inputs[ch->input] |= ch->in_channel;
    }

    /* guess channel maps when not explicitly defined */
    /* first try unused matching channels */
    for (i = 0; i < s->nb_channels; i++) {
        ChannelMap *ch = &s->channels[i];

        if (ch->input < 0)
            guess_map_matching(ctx, ch, inputs);
    }

    /* if the above failed, try to find _any_ unused input channel */
    for (i = 0; i < s->nb_channels; i++) {
        ChannelMap *ch = &s->channels[i];

        if (ch->input < 0)
            guess_map_any(ctx, ch, inputs);

        if (ch->input < 0) {
            av_log(ctx, AV_LOG_ERROR, "Could not find input channel for "
                   "output channel '%s'.\n",
                   av_get_channel_name(ch->out_channel));
            goto fail;
        }

        ch->in_channel_idx = av_get_channel_layout_channel_index(ctx->inputs[ch->input]->channel_layout,
                                                                 ch->in_channel);
    }

    /* print mappings */
    av_log(ctx, AV_LOG_VERBOSE, "mappings: ");
    for (i = 0; i < s->nb_channels; i++) {
        ChannelMap *ch = &s->channels[i];
        av_log(ctx, AV_LOG_VERBOSE, "%d.%s => %s ", ch->input,
               av_get_channel_name(ch->in_channel),
               av_get_channel_name(ch->out_channel));
    }
    av_log(ctx, AV_LOG_VERBOSE, "\n");

    for (i = 0; i < ctx->nb_inputs; i++) {
        if (!inputs[i])
            av_log(ctx, AV_LOG_WARNING, "No channels are used from input "
                   "stream %d.\n", i);
    }

fail:
    av_freep(&inputs);
    return ret;
}