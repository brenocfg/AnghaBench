#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int width; int height; scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_23__ {int /*<<< orphan*/  flags; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_22__ {int const* hsample; int const* vsample; int /*<<< orphan*/  matrix; int /*<<< orphan*/  pred; int /*<<< orphan*/  scantable; } ;
struct TYPE_21__ {scalar_t__ buf; } ;
typedef  TYPE_1__ PutBitContext ;
typedef  TYPE_2__ LJpegEncContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AV_INPUT_BUFFER_MIN_SIZE ; 
 scalar_t__ AV_PIX_FMT_BGR0 ; 
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_BGRA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_picture_header (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_picture_trailer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ff_mjpeg_escape_FF (TYPE_1__*,int) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_1__*) ; 
 int /*<<< orphan*/  init_put_bits (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ljpeg_encode_bgr (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int ljpeg_encode_yuv (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int put_bits_count (TYPE_1__*) ; 
 scalar_t__ put_bits_ptr (TYPE_1__*) ; 

__attribute__((used)) static int ljpeg_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                              const AVFrame *pict, int *got_packet)
{
    LJpegEncContext *s = avctx->priv_data;
    PutBitContext pb;
    const int width  = avctx->width;
    const int height = avctx->height;
    const int mb_width  = (width  + s->hsample[0] - 1) / s->hsample[0];
    const int mb_height = (height + s->vsample[0] - 1) / s->vsample[0];
    int max_pkt_size = AV_INPUT_BUFFER_MIN_SIZE;
    int ret, header_bits;

    if(    avctx->pix_fmt == AV_PIX_FMT_BGR0
        || avctx->pix_fmt == AV_PIX_FMT_BGR24)
        max_pkt_size += width * height * 3 * 4;
    else if(avctx->pix_fmt == AV_PIX_FMT_BGRA)
        max_pkt_size += width * height * 4 * 4;
    else {
        max_pkt_size += mb_width * mb_height * 3 * 4
                        * s->hsample[0] * s->vsample[0];
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, max_pkt_size, 0)) < 0)
        return ret;

    init_put_bits(&pb, pkt->data, pkt->size);

    ff_mjpeg_encode_picture_header(avctx, &pb, &s->scantable,
                                   s->pred, s->matrix, s->matrix);

    header_bits = put_bits_count(&pb);

    if(    avctx->pix_fmt == AV_PIX_FMT_BGR0
        || avctx->pix_fmt == AV_PIX_FMT_BGRA
        || avctx->pix_fmt == AV_PIX_FMT_BGR24)
        ret = ljpeg_encode_bgr(avctx, &pb, pict);
    else
        ret = ljpeg_encode_yuv(avctx, &pb, pict);
    if (ret < 0)
        return ret;

    emms_c();

    ff_mjpeg_escape_FF(&pb, header_bits >> 3);
    ff_mjpeg_encode_picture_trailer(&pb, header_bits);

    flush_put_bits(&pb);
    pkt->size   = put_bits_ptr(&pb) - pb.buf;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}