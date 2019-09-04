#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {unsigned int width; unsigned int height; TYPE_3__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int bpp; TYPE_2__* frame2; int /*<<< orphan*/ * delta; int /*<<< orphan*/  delta_size; TYPE_1__* frame1; int /*<<< orphan*/  gb; } ;
struct TYPE_12__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_5__*,char*,unsigned int) ; 
 unsigned int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int decode_zlib (TYPE_5__*,TYPE_4__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_move(AVCodecContext *avctx,
                       AVPacket *avpkt, unsigned size)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    GetByteContext mc;
    unsigned pos, compression, nb_moves;
    unsigned uncompressed_size;
    int ret;

    pos = bytestream2_tell(gb);
    bytestream2_skip(gb, 8);
    nb_moves = bytestream2_get_le32(gb);
    bytestream2_skip(gb, 8);
    compression = bytestream2_get_le32(gb);

    if (nb_moves > INT32_MAX / 16 || nb_moves > avctx->width * avctx->height)
        return AVERROR_INVALIDDATA;

    uncompressed_size = 16 * nb_moves;

    if (compression == 1) {
        ret = decode_zlib(avctx, avpkt,
                          size - (bytestream2_tell(gb) - pos),
                          uncompressed_size);
        if (ret < 0)
            return ret;
        bytestream2_init(&mc, s->delta, uncompressed_size);
    } else if (compression == 0) {
        bytestream2_init(&mc, avpkt->data + bytestream2_tell(gb),
                         bytestream2_get_bytes_left(gb));
    } else if (compression == 2) {
        avpriv_request_sample(avctx, "compression %d", compression);
        return AVERROR_PATCHWELCOME;
    } else {
        return AVERROR_INVALIDDATA;
    }

    if (bytestream2_get_bytes_left(&mc) < uncompressed_size)
        return AVERROR_INVALIDDATA;

    for (int i = 0; i < nb_moves; i++) {
        int type, start_x, start_y, end_x, end_y, mov_x, mov_y;
        uint8_t *e2, *b1, *b2;
        int w, h;

        type = bytestream2_get_le16(&mc);
        start_x = bytestream2_get_le16(&mc);
        start_y = bytestream2_get_le16(&mc);
        end_x = bytestream2_get_le16(&mc);
        end_y = bytestream2_get_le16(&mc);
        mov_x = bytestream2_get_le16(&mc);
        mov_y = bytestream2_get_le16(&mc);
        bytestream2_skip(&mc, 2);

        if (start_x >= avctx->width || start_y >= avctx->height ||
            end_x >= avctx->width || end_y >= avctx->height ||
            mov_x >= avctx->width || mov_y >= avctx->height) {
            continue;
        }

        if (start_x >= end_x || start_y >= end_y)
            continue;

        w = end_x - start_x;
        h = end_y - start_y;

        if (mov_x + w > avctx->width || mov_y + h > avctx->height)
            continue;

        if (!s->frame2->data[0] || !s->frame1->data[0])
            return AVERROR_INVALIDDATA;

        b1 = s->frame1->data[0] + s->frame1->linesize[0] * (start_y + h - 1) + start_x * s->bpp;
        b2 = s->frame2->data[0] + s->frame2->linesize[0] * (start_y + h - 1) + start_x * s->bpp;
        e2 = s->frame2->data[0] + s->frame2->linesize[0] * (mov_y + h - 1) + mov_x * s->bpp;

        if (type == 2) {
            for (int j = 0; j < h; j++) {
                memcpy(b1, b2, w * s->bpp);
                b1 -= s->frame1->linesize[0];
                b2 -= s->frame2->linesize[0];
            }
        } else if (type == 1) {
            for (int j = 0; j < h; j++) {
                memset(b2, 0, w * s->bpp);
                b2 -= s->frame2->linesize[0];
            }
        } else if (type == 0) {
            uint8_t *buffer;

            av_fast_padded_malloc(&s->delta, &s->delta_size, w * h * s->bpp);
            buffer = s->delta;
            if (!buffer)
                return AVERROR(ENOMEM);

            for (int j = 0; j < h; j++) {
                memcpy(buffer + j * w * s->bpp, e2, w * s->bpp);
                e2 -= s->frame2->linesize[0];
            }

            for (int j = 0; j < h; j++) {
                memcpy(b2, buffer + j * w * s->bpp, w * s->bpp);
                b2 -= s->frame2->linesize[0];
            }
        } else {
            return AVERROR_INVALIDDATA;
        }
    }

    bytestream2_skip(gb, size - (bytestream2_tell(gb) - pos));

    return 0;
}