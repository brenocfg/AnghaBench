#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int width; unsigned int height; TYPE_1__* priv_data; } ;
struct TYPE_5__ {unsigned int cursor_w; unsigned int cursor_h; int /*<<< orphan*/  delta; int /*<<< orphan*/  cursor; int /*<<< orphan*/  cursor_size; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int decode_zlib (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int decode_mous(AVCodecContext *avctx,
                       AVPacket *avpkt, unsigned size)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    unsigned w, h, pos, uncompressed_size;
    int ret;

    pos = bytestream2_tell(gb);
    bytestream2_skip(gb, 8);
    w = bytestream2_get_le32(gb);
    h = bytestream2_get_le32(gb);
    bytestream2_skip(gb, 12);
    uncompressed_size = bytestream2_get_le32(gb);

    if (w > avctx->width || h > avctx->height)
        return AVERROR_INVALIDDATA;

    if (uncompressed_size != 3 * w * h)
        return AVERROR_INVALIDDATA;

    av_fast_padded_malloc(&s->cursor, &s->cursor_size, uncompressed_size);
    if (!s->cursor)
        return AVERROR(ENOMEM);

    ret = decode_zlib(avctx, avpkt,
                      size - (bytestream2_tell(gb) - pos),
                      uncompressed_size);
    if (ret < 0)
        return ret;
    memcpy(s->cursor, s->delta, uncompressed_size);

    bytestream2_skip(gb, size - (bytestream2_tell(gb) - pos));

    s->cursor_w = w;
    s->cursor_h = h;

    return 0;
}