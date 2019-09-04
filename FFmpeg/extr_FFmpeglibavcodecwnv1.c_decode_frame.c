#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_12__ {int shift; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ WNV1Context ;
struct TYPE_15__ {int height; int width; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int key_frame; unsigned char** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_13__ {size_t* data; int size; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (size_t*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t* av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,size_t const) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 size_t* ff_reverse ; 
 int init_get_bits8 (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char wnv1_get_code (TYPE_1__* const,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    WNV1Context * const l = avctx->priv_data;
    const uint8_t *buf    = avpkt->data;
    int buf_size          = avpkt->size;
    AVFrame * const p     = data;
    unsigned char *Y,*U,*V;
    int i, j, ret;
    int prev_y = 0, prev_u = 0, prev_v = 0;
    uint8_t *rbuf;

    if (buf_size < 8 + avctx->height * (avctx->width/2)/8) {
        av_log(avctx, AV_LOG_ERROR, "Packet size %d is too small\n", buf_size);
        return AVERROR_INVALIDDATA;
    }

    rbuf = av_malloc(buf_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!rbuf) {
        av_log(avctx, AV_LOG_ERROR, "Cannot allocate temporary buffer\n");
        return AVERROR(ENOMEM);
    }
    memset(rbuf + buf_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0) {
        av_free(rbuf);
        return ret;
    }
    p->key_frame = 1;

    for (i = 8; i < buf_size; i++)
        rbuf[i] = ff_reverse[buf[i]];

    if ((ret = init_get_bits8(&l->gb, rbuf + 8, buf_size - 8)) < 0)
        return ret;

    if (buf[2] >> 4 == 6)
        l->shift = 2;
    else {
        l->shift = 8 - (buf[2] >> 4);
        if (l->shift > 4) {
            avpriv_request_sample(avctx,
                                  "Unknown WNV1 frame header value %i",
                                  buf[2] >> 4);
            l->shift = 4;
        }
        if (l->shift < 1) {
            avpriv_request_sample(avctx,
                                  "Unknown WNV1 frame header value %i",
                                  buf[2] >> 4);
            l->shift = 1;
        }
    }

    Y = p->data[0];
    U = p->data[1];
    V = p->data[2];
    for (j = 0; j < avctx->height; j++) {
        for (i = 0; i < avctx->width / 2; i++) {
            Y[i * 2] = wnv1_get_code(l, prev_y);
            prev_u = U[i] = wnv1_get_code(l, prev_u);
            prev_y = Y[(i * 2) + 1] = wnv1_get_code(l, Y[i * 2]);
            prev_v = V[i] = wnv1_get_code(l, prev_v);
        }
        Y += p->linesize[0];
        U += p->linesize[1];
        V += p->linesize[2];
    }


    *got_frame      = 1;
    av_free(rbuf);

    return buf_size;
}