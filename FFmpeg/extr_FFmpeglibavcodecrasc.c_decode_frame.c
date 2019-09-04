#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_24__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_30__ {int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * data; } ;
struct TYPE_29__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {TYPE_4__* frame; int /*<<< orphan*/  skip_cursor; TYPE_24__* frame2; TYPE_1__* frame1; int /*<<< orphan*/  gb; } ;
struct TYPE_27__ {int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 unsigned int BNDL ; 
#define  DLTA 134 
 scalar_t__ EMPT ; 
#define  FINT 133 
#define  INIT 132 
 unsigned int KBND ; 
#define  KFRM 131 
#define  MOUS 130 
#define  MOVE 129 
#define  MPOS 128 
 unsigned int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bytestream2_peek_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  copy_plane (TYPE_5__*,TYPE_24__*,TYPE_4__*) ; 
 int decode_dlta (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int decode_fint (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int decode_kfrm (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int decode_mous (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int decode_move (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int decode_mpos (TYPE_5__*,TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  draw_cursor (TYPE_5__*) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int ret, intra = 0;
    AVFrame *frame = data;

    bytestream2_init(gb, avpkt->data, avpkt->size);

    if (bytestream2_peek_le32(gb) == EMPT)
        return avpkt->size;

    s->frame = frame;

    while (bytestream2_get_bytes_left(gb) > 0) {
        unsigned type, size = 0;

        if (bytestream2_get_bytes_left(gb) < 8)
            return AVERROR_INVALIDDATA;

        type = bytestream2_get_le32(gb);
        if (type == KBND || type == BNDL) {
            intra = type == KBND;
            type = bytestream2_get_le32(gb);
        }

        size = bytestream2_get_le32(gb);
        if (bytestream2_get_bytes_left(gb) < size)
            return AVERROR_INVALIDDATA;

        switch (type) {
        case FINT:
        case INIT:
            ret = decode_fint(avctx, avpkt, size);
            break;
        case KFRM:
            ret = decode_kfrm(avctx, avpkt, size);
            break;
        case DLTA:
            ret = decode_dlta(avctx, avpkt, size);
            break;
        case MOVE:
            ret = decode_move(avctx, avpkt, size);
            break;
        case MOUS:
            ret = decode_mous(avctx, avpkt, size);
            break;
        case MPOS:
            ret = decode_mpos(avctx, avpkt, size);
            break;
        default:
            bytestream2_skip(gb, size);
        }

        if (ret < 0)
            return ret;
    }

    if (!s->frame2->data[0] || !s->frame1->data[0])
        return AVERROR_INVALIDDATA;

    if ((ret = ff_get_buffer(avctx, s->frame, 0)) < 0)
        return ret;

    copy_plane(avctx, s->frame2, s->frame);
    if (avctx->pix_fmt == AV_PIX_FMT_PAL8)
        memcpy(s->frame->data[1], s->frame2->data[1], 1024);
    if (!s->skip_cursor)
        draw_cursor(avctx);

    s->frame->key_frame = intra;
    s->frame->pict_type = intra ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;

    *got_frame = 1;

    return avpkt->size;
}