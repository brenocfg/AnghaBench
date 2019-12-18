#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int channels; double sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; TYPE_3__* dst; } ;
struct TYPE_6__ {int buf_size; int nb_in_channels; float lowcut; float lowcutf; float highcut; float highcutf; int /*<<< orphan*/  fifo; int /*<<< orphan*/  input; int /*<<< orphan*/  lfe_in; int /*<<< orphan*/ * input_levels; int /*<<< orphan*/  bc_in; int /*<<< orphan*/  br_in; int /*<<< orphan*/  bl_in; int /*<<< orphan*/  sr_in; int /*<<< orphan*/  sl_in; int /*<<< orphan*/  fr_in; int /*<<< orphan*/  fl_in; int /*<<< orphan*/  fc_in; int /*<<< orphan*/  level_in; int /*<<< orphan*/ * rdft; } ;
typedef  TYPE_1__ AudioSurroundContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CH_BACK_CENTER ; 
 int /*<<< orphan*/  AV_CH_BACK_LEFT ; 
 int /*<<< orphan*/  AV_CH_BACK_RIGHT ; 
 int /*<<< orphan*/  AV_CH_FRONT_CENTER ; 
 int /*<<< orphan*/  AV_CH_FRONT_LEFT ; 
 int /*<<< orphan*/  AV_CH_FRONT_RIGHT ; 
 int /*<<< orphan*/  AV_CH_LOW_FREQUENCY ; 
 int /*<<< orphan*/  AV_CH_SIDE_LEFT ; 
 int /*<<< orphan*/  AV_CH_SIDE_RIGHT ; 
 int /*<<< orphan*/  DFT_R2C ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_audio_fifo_alloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * av_calloc (int,int) ; 
 int av_get_channel_layout_channel_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_malloc_array (int,int) ; 
 int /*<<< orphan*/  av_rdft_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_get_audio_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ff_log2 (int) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioSurroundContext *s = ctx->priv;
    int ch;

    s->rdft = av_calloc(inlink->channels, sizeof(*s->rdft));
    if (!s->rdft)
        return AVERROR(ENOMEM);

    for (ch = 0; ch < inlink->channels; ch++) {
        s->rdft[ch]  = av_rdft_init(ff_log2(s->buf_size), DFT_R2C);
        if (!s->rdft[ch])
            return AVERROR(ENOMEM);
    }
    s->nb_in_channels = inlink->channels;
    s->input_levels = av_malloc_array(s->nb_in_channels, sizeof(*s->input_levels));
    if (!s->input_levels)
        return AVERROR(ENOMEM);
    for (ch = 0;  ch < s->nb_in_channels; ch++)
        s->input_levels[ch] = s->level_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_FRONT_CENTER);
    if (ch >= 0)
        s->input_levels[ch] *= s->fc_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_FRONT_LEFT);
    if (ch >= 0)
        s->input_levels[ch] *= s->fl_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_FRONT_RIGHT);
    if (ch >= 0)
        s->input_levels[ch] *= s->fr_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_SIDE_LEFT);
    if (ch >= 0)
        s->input_levels[ch] *= s->sl_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_SIDE_RIGHT);
    if (ch >= 0)
        s->input_levels[ch] *= s->sr_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_BACK_LEFT);
    if (ch >= 0)
        s->input_levels[ch] *= s->bl_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_BACK_RIGHT);
    if (ch >= 0)
        s->input_levels[ch] *= s->br_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_BACK_CENTER);
    if (ch >= 0)
        s->input_levels[ch] *= s->bc_in;
    ch = av_get_channel_layout_channel_index(inlink->channel_layout, AV_CH_LOW_FREQUENCY);
    if (ch >= 0)
        s->input_levels[ch] *= s->lfe_in;

    s->input = ff_get_audio_buffer(inlink, s->buf_size * 2);
    if (!s->input)
        return AVERROR(ENOMEM);

    s->fifo = av_audio_fifo_alloc(inlink->format, inlink->channels, s->buf_size);
    if (!s->fifo)
        return AVERROR(ENOMEM);

    s->lowcut = 1.f * s->lowcutf / (inlink->sample_rate * 0.5) * (s->buf_size / 2);
    s->highcut = 1.f * s->highcutf / (inlink->sample_rate * 0.5) * (s->buf_size / 2);

    return 0;
}