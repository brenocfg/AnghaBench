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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int slices; int planes; int slice_stride; int frame_pred; int /*<<< orphan*/ * slice_buffer; int /*<<< orphan*/  slice_bits; int /*<<< orphan*/  slice_bits_size; } ;
typedef  TYPE_1__ UtvideoContext ;
struct TYPE_15__ {int width; int height; int pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int* linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GBRAP 132 
#define  AV_PIX_FMT_GBRP 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV422P 129 
#define  AV_PIX_FMT_YUV444P 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_put_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_tell_p (int /*<<< orphan*/ *) ; 
 int encode_plane (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mangle_rgb_planes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*,int,int) ; 

__attribute__((used)) static int utvideo_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                const AVFrame *pic, int *got_packet)
{
    UtvideoContext *c = avctx->priv_data;
    PutByteContext pb;

    uint32_t frame_info;

    uint8_t *dst;

    int width = avctx->width, height = avctx->height;
    int i, ret = 0;

    /* Allocate a new packet if needed, and set it to the pointer dst */
    ret = ff_alloc_packet2(avctx, pkt, (256 + 4 * c->slices + width * height) *
                           c->planes + 4, 0);

    if (ret < 0)
        return ret;

    dst = pkt->data;

    bytestream2_init_writer(&pb, dst, pkt->size);

    av_fast_padded_malloc(&c->slice_bits, &c->slice_bits_size, width * height + 4);

    if (!c->slice_bits) {
        av_log(avctx, AV_LOG_ERROR, "Cannot allocate temporary buffer 2.\n");
        return AVERROR(ENOMEM);
    }

    /* In case of RGB, mangle the planes to Ut Video's format */
    if (avctx->pix_fmt == AV_PIX_FMT_GBRAP || avctx->pix_fmt == AV_PIX_FMT_GBRP)
        mangle_rgb_planes(c->slice_buffer, c->slice_stride, pic->data,
                          c->planes, pic->linesize, width, height);

    /* Deal with the planes */
    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_GBRP:
    case AV_PIX_FMT_GBRAP:
        for (i = 0; i < c->planes; i++) {
            ret = encode_plane(avctx, c->slice_buffer[i] + 2 * c->slice_stride,
                               c->slice_buffer[i], c->slice_stride, i,
                               width, height, &pb);

            if (ret) {
                av_log(avctx, AV_LOG_ERROR, "Error encoding plane %d.\n", i);
                return ret;
            }
        }
        break;
    case AV_PIX_FMT_YUV444P:
        for (i = 0; i < c->planes; i++) {
            ret = encode_plane(avctx, pic->data[i], c->slice_buffer[0],
                               pic->linesize[i], i, width, height, &pb);

            if (ret) {
                av_log(avctx, AV_LOG_ERROR, "Error encoding plane %d.\n", i);
                return ret;
            }
        }
        break;
    case AV_PIX_FMT_YUV422P:
        for (i = 0; i < c->planes; i++) {
            ret = encode_plane(avctx, pic->data[i], c->slice_buffer[0],
                               pic->linesize[i], i, width >> !!i, height, &pb);

            if (ret) {
                av_log(avctx, AV_LOG_ERROR, "Error encoding plane %d.\n", i);
                return ret;
            }
        }
        break;
    case AV_PIX_FMT_YUV420P:
        for (i = 0; i < c->planes; i++) {
            ret = encode_plane(avctx, pic->data[i], c->slice_buffer[0],
                               pic->linesize[i], i, width >> !!i, height >> !!i,
                               &pb);

            if (ret) {
                av_log(avctx, AV_LOG_ERROR, "Error encoding plane %d.\n", i);
                return ret;
            }
        }
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown pixel format: %d\n",
               avctx->pix_fmt);
        return AVERROR_INVALIDDATA;
    }

    /*
     * Write frame information (LE 32-bit unsigned)
     * into the output packet.
     * Contains the prediction method.
     */
    frame_info = c->frame_pred << 8;
    bytestream2_put_le32(&pb, frame_info);

    /*
     * At least currently Ut Video is IDR only.
     * Set flags accordingly.
     */
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->key_frame = 1;
    avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    pkt->size   = bytestream2_tell_p(&pb);
    pkt->flags |= AV_PKT_FLAG_KEY;

    /* Packet should be done */
    *got_packet = 1;

    return 0;
}