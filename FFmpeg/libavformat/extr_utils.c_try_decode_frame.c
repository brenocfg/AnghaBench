#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_15__ ;

/* Type definitions */
typedef  enum AVDiscard { ____Placeholder_AVDiscard } AVDiscard ;
struct TYPE_30__ {int codec_id; int skip_frame; scalar_t__ codec_type; TYPE_15__* codec; } ;
struct TYPE_29__ {char* codec_whitelist; } ;
struct TYPE_28__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  nb_decoded_frames; int /*<<< orphan*/  codec_info_nb_frames; TYPE_3__* info; TYPE_2__* codecpar; TYPE_1__* internal; } ;
struct TYPE_26__ {int found_decoder; } ;
struct TYPE_25__ {int codec_id; } ;
struct TYPE_24__ {TYPE_7__* avctx; } ;
struct TYPE_23__ {int capabilities; } ;
typedef  int /*<<< orphan*/  AVSubtitle ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_6__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_7__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVDISCARD_ALL ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int AV_CODEC_CAP_CHANNEL_CONF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int avcodec_decode_subtitle2 (TYPE_7__*,int /*<<< orphan*/ *,int*,TYPE_5__*) ; 
 int /*<<< orphan*/  avcodec_is_open (TYPE_7__*) ; 
 int avcodec_open2 (TYPE_7__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int avcodec_receive_frame (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int avcodec_send_packet (TYPE_7__*,TYPE_5__*) ; 
 scalar_t__ avpriv_codec_get_cap_skip_frame_fill_param (TYPE_15__*) ; 
 int /*<<< orphan*/ * find_probe_decoder (TYPE_6__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  has_codec_parameters (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_decode_delay_been_guessed (TYPE_4__*) ; 

__attribute__((used)) static int try_decode_frame(AVFormatContext *s, AVStream *st,
                            const AVPacket *avpkt, AVDictionary **options)
{
    AVCodecContext *avctx = st->internal->avctx;
    const AVCodec *codec;
    int got_picture = 1, ret = 0;
    AVFrame *frame = av_frame_alloc();
    AVSubtitle subtitle;
    AVPacket pkt = *avpkt;
    int do_skip_frame = 0;
    enum AVDiscard skip_frame;

    if (!frame)
        return AVERROR(ENOMEM);

    if (!avcodec_is_open(avctx) &&
        st->info->found_decoder <= 0 &&
        (st->codecpar->codec_id != -st->info->found_decoder || !st->codecpar->codec_id)) {
        AVDictionary *thread_opt = NULL;

        codec = find_probe_decoder(s, st, st->codecpar->codec_id);

        if (!codec) {
            st->info->found_decoder = -st->codecpar->codec_id;
            ret                     = -1;
            goto fail;
        }

        /* Force thread count to 1 since the H.264 decoder will not extract
         * SPS and PPS to extradata during multi-threaded decoding. */
        av_dict_set(options ? options : &thread_opt, "threads", "1", 0);
        if (s->codec_whitelist)
            av_dict_set(options ? options : &thread_opt, "codec_whitelist", s->codec_whitelist, 0);
        ret = avcodec_open2(avctx, codec, options ? options : &thread_opt);
        if (!options)
            av_dict_free(&thread_opt);
        if (ret < 0) {
            st->info->found_decoder = -avctx->codec_id;
            goto fail;
        }
        st->info->found_decoder = 1;
    } else if (!st->info->found_decoder)
        st->info->found_decoder = 1;

    if (st->info->found_decoder < 0) {
        ret = -1;
        goto fail;
    }

    if (avpriv_codec_get_cap_skip_frame_fill_param(avctx->codec)) {
        do_skip_frame = 1;
        skip_frame = avctx->skip_frame;
        avctx->skip_frame = AVDISCARD_ALL;
    }

    while ((pkt.size > 0 || (!pkt.data && got_picture)) &&
           ret >= 0 &&
           (!has_codec_parameters(st, NULL) || !has_decode_delay_been_guessed(st) ||
            (!st->codec_info_nb_frames &&
             (avctx->codec->capabilities & AV_CODEC_CAP_CHANNEL_CONF)))) {
        got_picture = 0;
        if (avctx->codec_type == AVMEDIA_TYPE_VIDEO ||
            avctx->codec_type == AVMEDIA_TYPE_AUDIO) {
            ret = avcodec_send_packet(avctx, &pkt);
            if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
                break;
            if (ret >= 0)
                pkt.size = 0;
            ret = avcodec_receive_frame(avctx, frame);
            if (ret >= 0)
                got_picture = 1;
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                ret = 0;
        } else if (avctx->codec_type == AVMEDIA_TYPE_SUBTITLE) {
            ret = avcodec_decode_subtitle2(avctx, &subtitle,
                                           &got_picture, &pkt);
            if (ret >= 0)
                pkt.size = 0;
        }
        if (ret >= 0) {
            if (got_picture)
                st->nb_decoded_frames++;
            ret       = got_picture;
        }
    }

    if (!pkt.data && !got_picture)
        ret = -1;

fail:
    if (do_skip_frame) {
        avctx->skip_frame = skip_frame;
    }

    av_frame_free(&frame);
    return ret;
}