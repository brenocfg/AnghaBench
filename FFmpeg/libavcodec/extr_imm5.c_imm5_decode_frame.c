#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  chroma_sample_location; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int size; int* data; } ;
struct TYPE_13__ {TYPE_3__* hevc_avctx; TYPE_3__* h264_avctx; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ IMM5Context ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned long long AV_RL32 (int*) ; 
 TYPE_11__* IMM5_units ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_make_writable (TYPE_2__*) ; 
 int avcodec_receive_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avcodec_send_packet (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imm5_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    IMM5Context *ctx = avctx->priv_data;
    AVFrame *frame = data;
    AVCodecContext *codec_avctx = ctx->h264_avctx;
    int ret;

    if (avpkt->size > 24 && avpkt->data[8] <= 1 && AV_RL32(avpkt->data + 4) + 24ULL <= avpkt->size) {
        int codec_type = avpkt->data[1];
        int index = avpkt->data[10];
        int new_size = AV_RL32(avpkt->data + 4);
        int offset, off;

        if (codec_type == 0xA) {
            codec_avctx = ctx->hevc_avctx;
        } else if (index == 17) {
            index = 4;
        } else if (index == 18) {
            index = 5;
        }

        if (index >= 1 && index <= 12) {
            ret = av_packet_make_writable(avpkt);
            if (ret < 0)
                return ret;

            index -= 1;
            off = offset = IMM5_units[index].len;
            if (codec_type == 2) {
                offset += IMM5_units[12].len;
            } else {
                offset += IMM5_units[13].len;
            }

            avpkt->data += 24 - offset;
            avpkt->size = new_size + offset;

            memcpy(avpkt->data, IMM5_units[index].bits, IMM5_units[index].len);
            if (codec_type == 2) {
                memcpy(avpkt->data + off, IMM5_units[12].bits, IMM5_units[12].len);
            } else {
                memcpy(avpkt->data + off, IMM5_units[13].bits, IMM5_units[13].len);
            }
        } else {
            avpkt->data += 24;
            avpkt->size -= 24;
        }
    }

    ret = avcodec_send_packet(codec_avctx, avpkt);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error submitting a packet for decoding\n");
        return ret;
    }

    ret = avcodec_receive_frame(codec_avctx, frame);
    if (ret < 0)
        return ret;

    avctx->pix_fmt      = codec_avctx->pix_fmt;
    avctx->coded_width  = codec_avctx->coded_width;
    avctx->coded_height = codec_avctx->coded_height;
    avctx->width        = codec_avctx->width;
    avctx->height       = codec_avctx->height;
    avctx->bit_rate     = codec_avctx->bit_rate;
    avctx->colorspace   = codec_avctx->colorspace;
    avctx->color_range  = codec_avctx->color_range;
    avctx->color_trc    = codec_avctx->color_trc;
    avctx->color_primaries = codec_avctx->color_primaries;
    avctx->chroma_sample_location = codec_avctx->chroma_sample_location;

    *got_frame = 1;

    return avpkt->size;
}