#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ codec_type; } ;
struct TYPE_16__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_15__ {size_t stream_index; } ;
struct TYPE_14__ {scalar_t__ codec_info_nb_frames; TYPE_4__* codec; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int av_read_frame (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  avcodec_close (TYPE_4__*) ; 
 int try_decode_video_frame (TYPE_4__*,TYPE_2__*,int) ; 

__attribute__((used)) static int find_video_stream_info(AVFormatContext *fmt_ctx, int decode)
{
    int ret = 0;
    int i, done = 0;
    AVPacket pkt;

    av_init_packet(&pkt);

    while (!done) {
        AVCodecContext *codec_ctx = NULL;
        AVStream *st;

        if ((ret = av_read_frame(fmt_ctx, &pkt)) < 0) {
            av_log(fmt_ctx, AV_LOG_ERROR, "Failed to read frame\n");
            goto end;
        }

        st = fmt_ctx->streams[pkt.stream_index];
        codec_ctx = st->codec;

        /* Writing to AVStream.codec_info_nb_frames must not be done by
         * user applications. It is done here for testing purposing as
         * find_video_stream_info tries to mimic avformat_find_stream_info
         * which writes to this field.
         * */
        if (codec_ctx->codec_type != AVMEDIA_TYPE_VIDEO ||
            st->codec_info_nb_frames++ > 0) {
            av_packet_unref(&pkt);
            continue;
        }

        ret = try_decode_video_frame(codec_ctx, &pkt, decode);
        if (ret < 0) {
            av_log(fmt_ctx, AV_LOG_ERROR, "Failed to decode video frame\n");
            goto end;
        }

        av_packet_unref(&pkt);

        /* check if all video streams have demuxed a packet */
        done = 1;
        for (i = 0; i < fmt_ctx->nb_streams; i++) {
            st = fmt_ctx->streams[i];
            codec_ctx = st->codec;

            if (codec_ctx->codec_type != AVMEDIA_TYPE_VIDEO)
                continue;

            done &= st->codec_info_nb_frames > 0;
        }
    }

end:
    av_packet_unref(&pkt);

    /* close all codecs opened in try_decode_video_frame */
    for (i = 0; i < fmt_ctx->nb_streams; i++) {
        AVStream *st = fmt_ctx->streams[i];
        avcodec_close(st->codec);
    }

    return ret < 0;
}