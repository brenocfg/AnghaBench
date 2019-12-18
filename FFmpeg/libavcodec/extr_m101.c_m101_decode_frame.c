#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int width; int* extradata; scalar_t__ pix_fmt; int height; } ;
struct TYPE_10__ {int key_frame; int interlaced_frame; int top_field_first; int** data; int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {int* data; int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PIX_FMT_YUV422P10 ; 
 int AV_RL32 (int*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int m101_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                      AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int stride, ret;
    int x, y;
    int min_stride = 2 * avctx->width;
    int bits = avctx->extradata[2*4];
    AVFrame *frame = data;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    frame->pict_type = AV_PICTURE_TYPE_I;
    frame->key_frame = 1;

    stride = AV_RL32(avctx->extradata + 5*4);

    if (avctx->pix_fmt == AV_PIX_FMT_YUV422P10)
        min_stride = (avctx->width + 15) / 16 * 40;

    if (stride < min_stride || avpkt->size < stride * (uint64_t)avctx->height) {
        av_log(avctx, AV_LOG_ERROR, "stride (%d) is invalid for packet sized %d\n",
               stride, avpkt->size);
        return AVERROR_INVALIDDATA;
    }

    frame->interlaced_frame = ((avctx->extradata[3*4] & 3) != 3);
    if (frame->interlaced_frame)
        frame->top_field_first = avctx->extradata[3*4] & 1;

    for (y = 0; y < avctx->height; y++) {
        int src_y = y;
        if (frame->interlaced_frame)
            src_y = ((y&1)^frame->top_field_first) ? y/2 : (y/2 + avctx->height/2);
        if (bits == 8) {
            uint8_t *line = frame->data[0] + y*frame->linesize[0];
            memcpy(line, buf + src_y*stride, 2*avctx->width);
        } else {
            int block;
            uint16_t *luma = (uint16_t*)&frame->data[0][y*frame->linesize[0]];
            uint16_t *cb   = (uint16_t*)&frame->data[1][y*frame->linesize[1]];
            uint16_t *cr   = (uint16_t*)&frame->data[2][y*frame->linesize[2]];
            for (block = 0; 16*block < avctx->width; block ++) {
                const uint8_t *buf_src = buf + src_y*stride + 40*block;
                for (x = 0; x < 16 && x + 16*block < avctx->width; x++) {
                    int xd = x + 16*block;
                    if (x&1) {
                        luma [xd] = (4*buf_src[2*x + 0]) + ((buf_src[32 + (x>>1)]>>4)&3);
                    } else {
                        luma [xd] = (4*buf_src[2*x + 0]) +  (buf_src[32 + (x>>1)]    &3);
                        cb[xd>>1] = (4*buf_src[2*x + 1]) + ((buf_src[32 + (x>>1)]>>2)&3);
                        cr[xd>>1] = (4*buf_src[2*x + 3]) +  (buf_src[32 + (x>>1)]>>6);
                    }
                }
            }
        }
    }

    *got_frame = 1;
    return avpkt->size;
}