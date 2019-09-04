#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* bswap_buf ) (scalar_t__*,scalar_t__*,int) ;} ;
struct TYPE_15__ {int* table_bits; int* bitstream_bits; TYPE_12__* vlc; TYPE_1__ bdsp; int /*<<< orphan*/  bitstream_bits_size; scalar_t__* table; int /*<<< orphan*/  table_bits_size; } ;
typedef  TYPE_2__ YLCContext ;
struct TYPE_16__ {void* f; } ;
typedef  TYPE_3__ ThreadFrame ;
struct TYPE_19__ {int height; int width; TYPE_2__* priv_data; } ;
struct TYPE_18__ {int** data; int* linesize; int key_frame; int /*<<< orphan*/  pict_type; } ;
struct TYPE_17__ {int* data; int size; } ;
struct TYPE_13__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int AV_RL32 (int const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_fast_malloc (int**,int /*<<< orphan*/ *,int) ; 
 int build_vlc (TYPE_6__*,TYPE_12__*,scalar_t__*) ; 
 int ff_thread_get_buffer (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_long (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,scalar_t__*,int) ; 
 int* table_u ; 
 int* table_v ; 
 int* table_y1 ; 
 int* table_y2 ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    int TL[4] = { 128, 128, 128, 128 };
    int L[4]  = { 128, 128, 128, 128 };
    YLCContext *s = avctx->priv_data;
    ThreadFrame frame = { .f = data };
    const uint8_t *buf = avpkt->data;
    int ret, x, y, toffset, boffset;
    AVFrame * const p = data;
    GetBitContext gb;
    uint8_t *dst;

    if (avpkt->size <= 16)
        return AVERROR_INVALIDDATA;

    if (AV_RL32(buf) != MKTAG('Y', 'L', 'C', '0') ||
        AV_RL32(buf + 4) != 0)
        return AVERROR_INVALIDDATA;

    toffset = AV_RL32(buf + 8);
    if (toffset < 16 || toffset >= avpkt->size)
        return AVERROR_INVALIDDATA;

    boffset = AV_RL32(buf + 12);
    if (toffset >= boffset || boffset >= avpkt->size)
        return AVERROR_INVALIDDATA;

    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        return ret;

    av_fast_malloc(&s->table_bits, &s->table_bits_size,
                   boffset - toffset + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!s->table_bits)
        return AVERROR(ENOMEM);

    memcpy(s->table_bits, avpkt->data + toffset, boffset - toffset);
    memset(s->table_bits + boffset - toffset, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    s->bdsp.bswap_buf((uint32_t *) s->table_bits,
                      (uint32_t *) s->table_bits,
                      (boffset - toffset + 3) >> 2);
    if ((ret = init_get_bits8(&gb, s->table_bits, boffset - toffset)) < 0)
        return ret;

    for (x = 0; x < 1024; x++) {
        unsigned len = get_unary(&gb, 1, 31);
        uint32_t val = ((1U << len) - 1) + get_bits_long(&gb, len);

        s->table[x] = val;
    }

    ret = build_vlc(avctx, &s->vlc[0], &s->table[0  ]);
    if (ret < 0)
        return ret;
    ret = build_vlc(avctx, &s->vlc[1], &s->table[256]);
    if (ret < 0)
        return ret;
    ret = build_vlc(avctx, &s->vlc[2], &s->table[512]);
    if (ret < 0)
        return ret;
    ret = build_vlc(avctx, &s->vlc[3], &s->table[768]);
    if (ret < 0)
        return ret;

    av_fast_malloc(&s->bitstream_bits, &s->bitstream_bits_size,
                   avpkt->size - boffset + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!s->bitstream_bits)
        return AVERROR(ENOMEM);

    memcpy(s->bitstream_bits, avpkt->data + boffset, avpkt->size - boffset);
    memset(s->bitstream_bits + avpkt->size - boffset, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    s->bdsp.bswap_buf((uint32_t *) s->bitstream_bits,
                      (uint32_t *) s->bitstream_bits,
                      (avpkt->size - boffset) >> 2);
    if ((ret = init_get_bits8(&gb, s->bitstream_bits, avpkt->size - boffset)) < 0)
        return ret;

    dst = p->data[0];
    for (y = 0; y < avctx->height; y++) {
        memset(dst, 0, avctx->width * 2);
        dst += p->linesize[0];
    }

    dst = p->data[0];
    for (y = 0; y < avctx->height; y++) {
        for (x = 0; x < avctx->width * 2 && y < avctx->height;) {
            if (get_bits_left(&gb) <= 0)
                return AVERROR_INVALIDDATA;

            if (get_bits1(&gb)) {
                int val = get_vlc2(&gb, s->vlc[0].table, s->vlc[0].bits, 3);
                if (val < 0) {
                    return AVERROR_INVALIDDATA;
                } else if (val < 0xE1) {
                    dst[x    ] = table_y1[val];
                    dst[x + 1] = table_u[val];
                    dst[x + 2] = table_y2[val];
                    dst[x + 3] = table_v[val];
                    x += 4;
                } else {
                    int incr = (val - 0xDF) * 4;
                    if (x + incr >= avctx->width * 2) {
                        int iy = ((x + incr) / (avctx->width * 2));
                        x  = (x + incr) % (avctx->width * 2);
                        y += iy;
                        dst += iy * p->linesize[0];
                    } else {
                        x += incr;
                    }
                }
            } else {
                int y1, y2, u, v;

                y1 = get_vlc2(&gb, s->vlc[1].table, s->vlc[1].bits, 3);
                u  = get_vlc2(&gb, s->vlc[2].table, s->vlc[2].bits, 3);
                y2 = get_vlc2(&gb, s->vlc[1].table, s->vlc[1].bits, 3);
                v  = get_vlc2(&gb, s->vlc[3].table, s->vlc[3].bits, 3);
                if (y1 < 0 || y2 < 0 || u < 0 || v < 0)
                    return AVERROR_INVALIDDATA;
                dst[x    ] = y1;
                dst[x + 1] = u;
                dst[x + 2] = y1 + y2;
                dst[x + 3] = v;
                x += 4;
            }
        }
        dst += p->linesize[0];
    }

    dst = p->data[0];
    for (x = 0; x < avctx->width * 2; x += 4) {
        dst[x    ] =        dst[x    ] + L[0];
        dst[x + 2] = L[0] = dst[x + 2] + L[0];
        L[1] = dst[x + 1] + L[1];
        dst[x + 1] = L[1];
        L[2] = dst[x + 3] + L[2];
        dst[x + 3] = L[2];
    }
    dst += p->linesize[0];

    for (y = 1; y < avctx->height; y++) {
        x = 0;
        dst[x    ] =        dst[x    ] + L[0] + dst[x + 0 - p->linesize[0]] - TL[0];
        dst[x + 2] = L[0] = dst[x + 2] + L[0] + dst[x + 2 - p->linesize[0]] - TL[0];
        TL[0] = dst[x + 2 - p->linesize[0]];
        L[1] = dst[x + 1] + L[1] + dst[x + 1 - p->linesize[0]] - TL[1];
        dst[x + 1] = L[1];
        TL[1] = dst[x + 1 - p->linesize[0]];
        L[2] = dst[x + 3] + L[2] + dst[x + 3 - p->linesize[0]] - TL[2];
        dst[x + 3] = L[2];
        TL[2] = dst[x + 3 - p->linesize[0]];
        for (x = 4; x < avctx->width * 2; x += 4) {
            dst[x    ] =        dst[x    ] + L[0] + dst[x + 0 - p->linesize[0]] - TL[0];
            dst[x + 2] = L[0] = dst[x + 2] + L[0] + dst[x + 2 - p->linesize[0]] - TL[0];
            TL[0] = dst[x + 2 - p->linesize[0]];
            L[1] = dst[x + 1] + L[1] + dst[x + 1 - p->linesize[0]] - TL[1];
            dst[x + 1] = L[1];
            TL[1] = dst[x + 1 - p->linesize[0]];
            L[2] = dst[x + 3] + L[2] + dst[x + 3 - p->linesize[0]] - TL[2];
            dst[x + 3] = L[2];
            TL[2] = dst[x + 3 - p->linesize[0]];
        }
        dst += p->linesize[0];
    }

    p->pict_type = AV_PICTURE_TYPE_I;
    p->key_frame = 1;
    *got_frame   = 1;

    return avpkt->size;
}