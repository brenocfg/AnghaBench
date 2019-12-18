#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
typedef  unsigned long long int32_t ;
typedef  void* int16_t ;
struct TYPE_18__ {TYPE_2__* priv_data; } ;
struct TYPE_17__ {int* linesize; scalar_t__* data; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {int levels; unsigned long long*** scaling; unsigned int w; unsigned int h; TYPE_1__** band; int /*<<< orphan*/  prediction; int /*<<< orphan*/  gb; int /*<<< orphan*/  bc; } ;
struct TYPE_14__ {int width; int height; } ;
typedef  TYPE_2__ PixletContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t H ; 
 size_t V ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_tell (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lowpass_prediction (void**,int /*<<< orphan*/ ,int,int,int) ; 
 int read_highpass (TYPE_5__*,scalar_t__,int,TYPE_4__*) ; 
 int read_low_coeffs (TYPE_5__*,void**,int,int,int) ; 
 int /*<<< orphan*/  reconstruction (TYPE_5__*,void**,unsigned int,unsigned int,int,unsigned long long*,unsigned long long*) ; 
 void* sign_extend (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_plane(AVCodecContext *avctx, int plane,
                        AVPacket *avpkt, AVFrame *frame)
{
    PixletContext *ctx = avctx->priv_data;
    ptrdiff_t stride   = frame->linesize[plane] / 2;
    unsigned shift     = plane > 0;
    int16_t *dst;
    int i, ret;

    for (i = ctx->levels - 1; i >= 0; i--) {
        int32_t h = sign_extend(bytestream2_get_be32(&ctx->gb), 32);
        int32_t v = sign_extend(bytestream2_get_be32(&ctx->gb), 32);

        if (!h || !v)
            return AVERROR_INVALIDDATA;

        ctx->scaling[plane][H][i] = (1000000ULL << 32) / h;
        ctx->scaling[plane][V][i] = (1000000ULL << 32) / v;
    }

    bytestream2_skip(&ctx->gb, 4);

    dst    = (int16_t *)frame->data[plane];
    dst[0] = sign_extend(bytestream2_get_be16(&ctx->gb), 16);

    ret = init_get_bits8(&ctx->bc, avpkt->data + bytestream2_tell(&ctx->gb),
                         bytestream2_get_bytes_left(&ctx->gb));
    if (ret < 0)
        return ret;

    ret = read_low_coeffs(avctx, dst + 1, ctx->band[plane][0].width - 1,
                          ctx->band[plane][0].width - 1, 0);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "error in lowpass coefficients for plane %d, top row\n", plane);
        return ret;
    }

    ret = read_low_coeffs(avctx, dst + stride,
                          ctx->band[plane][0].height - 1, 1, stride);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "error in lowpass coefficients for plane %d, left column\n",
               plane);
        return ret;
    }

    ret = read_low_coeffs(avctx, dst + stride + 1,
                          (ctx->band[plane][0].width - 1) * (ctx->band[plane][0].height - 1),
                          ctx->band[plane][0].width - 1, stride);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "error in lowpass coefficients for plane %d, rest\n", plane);
        return ret;
    }

    bytestream2_skip(&ctx->gb, ret);
    if (bytestream2_get_bytes_left(&ctx->gb) <= 0) {
        av_log(avctx, AV_LOG_ERROR, "no bytes left\n");
        return AVERROR_INVALIDDATA;
    }

    ret = read_highpass(avctx, avpkt->data, plane, frame);
    if (ret < 0)
        return ret;

    lowpass_prediction(dst, ctx->prediction, ctx->band[plane][0].width,
                       ctx->band[plane][0].height, stride);

    reconstruction(avctx, (int16_t *)frame->data[plane], ctx->w >> shift,
                   ctx->h >> shift, stride, ctx->scaling[plane][H],
                   ctx->scaling[plane][V]);

    return 0;
}