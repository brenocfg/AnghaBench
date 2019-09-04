#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int channels; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int size; scalar_t__ data; } ;
struct TYPE_12__ {int word_bits; int word_bytes; int input_size; int key_present; int nb_programs; int multi_prog_warned; int nb_channels; size_t fr_code; int /*<<< orphan*/  prog_conf; scalar_t__ input; } ;
typedef  TYPE_1__ DBEContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_4POINT0 ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_5POINT1 ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_7POINT1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB24 (scalar_t__) ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int filter_frame (TYPE_1__*,void*) ; 
 int parse_audio (TYPE_1__*,int,int,int) ; 
 int parse_metadata (TYPE_1__*) ; 
 int parse_metadata_ext (TYPE_1__*) ; 
 int parse_meter (TYPE_1__*) ; 
 int /*<<< orphan*/ * sample_rate_tab ; 

__attribute__((used)) static int dolby_e_decode_frame(AVCodecContext *avctx, void *data,
                                int *got_frame_ptr, AVPacket *avpkt)
{
    DBEContext *s = avctx->priv_data;
    int i, j, hdr, ret;

    if (avpkt->size < 3)
        return AVERROR_INVALIDDATA;

    hdr = AV_RB24(avpkt->data);
    if ((hdr & 0xfffffe) == 0x7888e) {
        s->word_bits = 24;
    } else if ((hdr & 0xffffe0) == 0x788e0) {
        s->word_bits = 20;
    } else if ((hdr & 0xfffe00) == 0x78e00) {
        s->word_bits = 16;
    } else {
        av_log(avctx, AV_LOG_ERROR, "Invalid frame header\n");
        return AVERROR_INVALIDDATA;
    }

    s->word_bytes  = s->word_bits + 7 >> 3;
    s->input       = avpkt->data + s->word_bytes;
    s->input_size  = avpkt->size / s->word_bytes - 1;
    s->key_present = hdr >> 24 - s->word_bits & 1;

    if ((ret = parse_metadata(s)) < 0)
        return ret;

    if (s->nb_programs > 1 && !s->multi_prog_warned) {
        av_log(avctx, AV_LOG_WARNING, "Stream has %d programs (configuration %d), "
               "channels will be output in native order.\n", s->nb_programs, s->prog_conf);
        s->multi_prog_warned = 1;
    }

    switch (s->nb_channels) {
    case 4:
        avctx->channel_layout = AV_CH_LAYOUT_4POINT0;
        break;
    case 6:
        avctx->channel_layout = AV_CH_LAYOUT_5POINT1;
        break;
    case 8:
        avctx->channel_layout = AV_CH_LAYOUT_7POINT1;
        break;
    }

    avctx->channels    = s->nb_channels;
    avctx->sample_rate = sample_rate_tab[s->fr_code];
    avctx->sample_fmt  = AV_SAMPLE_FMT_FLTP;

    i = s->nb_channels / 2;
    j = s->nb_channels;
    if ((ret = parse_audio(s, 0, i, 0)) < 0)
        return ret;
    if ((ret = parse_audio(s, i, j, 0)) < 0)
        return ret;
    if ((ret = parse_metadata_ext(s)) < 0)
        return ret;
    if ((ret = parse_audio(s, 0, i, 1)) < 0)
        return ret;
    if ((ret = parse_audio(s, i, j, 1)) < 0)
        return ret;
    if ((ret = parse_meter(s)) < 0)
        return ret;
    if ((ret = filter_frame(s, data)) < 0)
        return ret;

    *got_frame_ptr = 1;
    return avpkt->size;
}