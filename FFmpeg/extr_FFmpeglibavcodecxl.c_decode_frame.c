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
typedef  int uint32_t ;
struct TYPE_11__ {int width; int height; } ;
struct TYPE_10__ {int key_frame; int** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {int* data; int size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int AV_RL32 (int const*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int* xl_table ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    AVFrame *const p   = data;
    uint8_t *Y, *U, *V;
    int i, j, ret;
    int stride;
    uint32_t val;
    int y0, y1, y2, y3 = 0, c0 = 0, c1 = 0;

    if (avctx->width % 4) {
        av_log(avctx, AV_LOG_ERROR, "width is not a multiple of 4\n");
        return AVERROR_INVALIDDATA;
    }
    if (buf_size < avctx->width * avctx->height) {
        av_log(avctx, AV_LOG_ERROR, "Packet is too small\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;
    p->pict_type = AV_PICTURE_TYPE_I;
    p->key_frame = 1;

    Y = p->data[0];
    U = p->data[1];
    V = p->data[2];

    stride = avctx->width - 4;

    for (i = 0; i < avctx->height; i++) {
        /* lines are stored in reversed order */
        buf += stride;

        for (j = 0; j < avctx->width; j += 4) {
            /* value is stored in LE dword with word swapped */
            val  = AV_RL32(buf);
            buf -= 4;
            val  = ((val >> 16) & 0xFFFF) | ((val & 0xFFFF) << 16);

            if (!j)
                y0 = (val & 0x1F) << 2;
            else
                y0 = y3 + xl_table[val & 0x1F];
            val >>= 5;
            y1    = y0 + xl_table[val & 0x1F];
            val >>= 5;
            y2    = y1 + xl_table[val & 0x1F];
            val >>= 6; /* align to word */
            y3    = y2 + xl_table[val & 0x1F];
            val >>= 5;
            if (!j)
                c0 = (val & 0x1F) << 2;
            else
                c0 += xl_table[val & 0x1F];
            val >>= 5;
            if (!j)
                c1 = (val & 0x1F) << 2;
            else
                c1 += xl_table[val & 0x1F];

            Y[j + 0] = y0 << 1;
            Y[j + 1] = y1 << 1;
            Y[j + 2] = y2 << 1;
            Y[j + 3] = y3 << 1;

            U[j >> 2] = c0 << 1;
            V[j >> 2] = c1 << 1;
        }

        buf += avctx->width + 4;
        Y   += p->linesize[0];
        U   += p->linesize[1];
        V   += p->linesize[2];
    }

    *got_frame = 1;

    return buf_size;
}