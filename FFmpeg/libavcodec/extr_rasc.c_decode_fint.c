#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__* data; } ;
struct TYPE_9__ {unsigned int width; unsigned int height; unsigned int pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_8__ {unsigned int stride; int bpp; TYPE_7__* frame2; TYPE_7__* frame1; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int AV_PIX_FMT_BGR0 ; 
 unsigned int AV_PIX_FMT_PAL8 ; 
 unsigned int AV_PIX_FMT_RGB555LE ; 
 unsigned int FFALIGN (unsigned int,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int bytestream2_peek_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_plane (TYPE_2__*,TYPE_7__*) ; 
 int ff_set_dimensions (TYPE_2__*,unsigned int,unsigned int) ; 
 int init_frames (TYPE_2__*) ; 

__attribute__((used)) static int decode_fint(AVCodecContext *avctx,
                       AVPacket *avpkt, unsigned size)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    unsigned w, h, fmt;
    int ret;

    if (bytestream2_peek_le32(gb) != 0x65) {
        if (!s->frame2->data[0] || !s->frame1->data[0])
            return AVERROR_INVALIDDATA;

        clear_plane(avctx, s->frame2);
        clear_plane(avctx, s->frame1);
        return 0;
    }
    if (bytestream2_get_bytes_left(gb) < 72)
        return AVERROR_INVALIDDATA;

    bytestream2_skip(gb, 8);
    w = bytestream2_get_le32(gb);
    h = bytestream2_get_le32(gb);
    bytestream2_skip(gb, 30);
    fmt = bytestream2_get_le16(gb);
    bytestream2_skip(gb, 24);

    switch (fmt) {
    case 8:  s->stride = FFALIGN(w, 4);
             s->bpp    = 1;
             fmt = AV_PIX_FMT_PAL8; break;
    case 16: s->stride = w * 2;
             s->bpp    = 2;
             fmt = AV_PIX_FMT_RGB555LE; break;
    case 32: s->stride = w * 4;
             s->bpp    = 4;
             fmt = AV_PIX_FMT_BGR0; break;
    default: return AVERROR_INVALIDDATA;
    }

    ret = ff_set_dimensions(avctx, w, h);
    if (ret < 0)
        return ret;
    avctx->width  = w;
    avctx->height = h;
    avctx->pix_fmt = fmt;

    ret = init_frames(avctx);
    if (ret < 0)
        return ret;

    if (avctx->pix_fmt == AV_PIX_FMT_PAL8) {
        uint32_t *pal = (uint32_t *)s->frame2->data[1];

        for (int i = 0; i < 256; i++)
            pal[i] = bytestream2_get_le32(gb) | 0xFF000000u;
    }

    return 0;
}