#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* idct_add ) (scalar_t__,int,int*) ;int /*<<< orphan*/  (* idct_put ) (scalar_t__,int,int*) ;int /*<<< orphan*/  (* add_pixels_clamped ) (int*,scalar_t__,int) ;int /*<<< orphan*/  (* idct ) (int*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_17__ {int flags; int* wblocks; int blocks_w; int* map; int blocks_h; int* block; TYPE_11__* avctx; TYPE_3__ idsp; int /*<<< orphan*/  map_size; int /*<<< orphan*/  wblocks_size; TYPE_2__* mvectors; TYPE_1__ gbyte; } ;
struct TYPE_16__ {int* linesize; scalar_t__* data; } ;
struct TYPE_14__ {int x; int y; } ;
struct TYPE_12__ {int coded_height; int coded_width; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AGMContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  copy_block8 (scalar_t__,scalar_t__,int,int,int) ; 
 int decode_inter_block (TYPE_5__*,int /*<<< orphan*/ *,int const*,int*,int*) ; 
 int decode_inter_blocks (TYPE_5__*,int /*<<< orphan*/ *,int const*,int*,int*) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub4 (int*) ; 
 int /*<<< orphan*/  stub5 (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,int,int*) ; 

__attribute__((used)) static int decode_inter_plane(AGMContext *s, GetBitContext *gb, int size,
                              const int *quant_matrix, AVFrame *frame,
                              AVFrame *prev, int plane)
{
    int ret, skip = 0;

    if ((ret = init_get_bits8(gb, s->gbyte.buffer, size)) < 0)
        return ret;

    if (s->flags == 3) {
        av_fast_padded_malloc(&s->wblocks, &s->wblocks_size,
                              64 * s->blocks_w * sizeof(*s->wblocks));
        if (!s->wblocks)
            return AVERROR(ENOMEM);

        av_fast_padded_malloc(&s->map, &s->map_size,
                              s->blocks_w * sizeof(*s->map));
        if (!s->map)
            return AVERROR(ENOMEM);

        for (int y = 0; y < s->blocks_h; y++) {
            ret = decode_inter_blocks(s, gb, quant_matrix, &skip, s->map);
            if (ret < 0)
                return ret;

            for (int x = 0; x < s->blocks_w; x++) {
                int shift = plane == 0;
                int mvpos = (y >> shift) * (s->blocks_w >> shift) + (x >> shift);
                int orig_mv_x = s->mvectors[mvpos].x;
                int mv_x = s->mvectors[mvpos].x / (1 + !shift);
                int mv_y = s->mvectors[mvpos].y / (1 + !shift);
                int h = s->avctx->coded_height >> !shift;
                int w = s->avctx->coded_width  >> !shift;
                int map = s->map[x];

                if (orig_mv_x >= -32) {
                    if (y * 8 + mv_y < 0 || y * 8 + mv_y >= h ||
                        x * 8 + mv_x < 0 || x * 8 + mv_x >= w)
                        return AVERROR_INVALIDDATA;

                    copy_block8(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                prev->data[plane] + ((s->blocks_h - 1 - y) * 8 - mv_y) * prev->linesize[plane] + (x * 8 + mv_x),
                                frame->linesize[plane], prev->linesize[plane], 8);
                    if (map) {
                        s->idsp.idct(s->wblocks + x * 64);
                        for (int i = 0; i < 64; i++)
                            s->wblocks[i + x * 64] = (s->wblocks[i + x * 64] + 1) & 0xFFFC;
                        s->idsp.add_pixels_clamped(&s->wblocks[x*64], frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                                   frame->linesize[plane]);
                    }
                } else if (map) {
                    s->idsp.idct_put(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                     frame->linesize[plane], s->wblocks + x * 64);
                }
            }
        }
    } else if (s->flags & 2) {
        for (int y = 0; y < s->blocks_h; y++) {
            for (int x = 0; x < s->blocks_w; x++) {
                int shift = plane == 0;
                int mvpos = (y >> shift) * (s->blocks_w >> shift) + (x >> shift);
                int orig_mv_x = s->mvectors[mvpos].x;
                int mv_x = s->mvectors[mvpos].x / (1 + !shift);
                int mv_y = s->mvectors[mvpos].y / (1 + !shift);
                int h = s->avctx->coded_height >> !shift;
                int w = s->avctx->coded_width  >> !shift;
                int map = 0;

                ret = decode_inter_block(s, gb, quant_matrix, &skip, &map);
                if (ret < 0)
                    return ret;

                if (orig_mv_x >= -32) {
                    if (y * 8 + mv_y < 0 || y * 8 + mv_y >= h ||
                        x * 8 + mv_x < 0 || x * 8 + mv_x >= w)
                        return AVERROR_INVALIDDATA;

                    copy_block8(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                prev->data[plane] + ((s->blocks_h - 1 - y) * 8 - mv_y) * prev->linesize[plane] + (x * 8 + mv_x),
                                frame->linesize[plane], prev->linesize[plane], 8);
                    if (map) {
                        s->idsp.idct(s->block);
                        for (int i = 0; i < 64; i++)
                            s->block[i] = (s->block[i] + 1) & 0xFFFC;
                        s->idsp.add_pixels_clamped(s->block, frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                                   frame->linesize[plane]);
                    }
                } else if (map) {
                    s->idsp.idct_put(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                     frame->linesize[plane], s->block);
                }
            }
        }
    } else if (s->flags & 1) {
        av_fast_padded_malloc(&s->wblocks, &s->wblocks_size,
                              64 * s->blocks_w * sizeof(*s->wblocks));
        if (!s->wblocks)
            return AVERROR(ENOMEM);

        av_fast_padded_malloc(&s->map, &s->map_size,
                              s->blocks_w * sizeof(*s->map));
        if (!s->map)
            return AVERROR(ENOMEM);

        for (int y = 0; y < s->blocks_h; y++) {
            ret = decode_inter_blocks(s, gb, quant_matrix, &skip, s->map);
            if (ret < 0)
                return ret;

            for (int x = 0; x < s->blocks_w; x++) {
                if (!s->map[x])
                    continue;
                s->idsp.idct_add(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                 frame->linesize[plane], s->wblocks + 64 * x);
            }
        }
    } else {
        for (int y = 0; y < s->blocks_h; y++) {
            for (int x = 0; x < s->blocks_w; x++) {
                int map = 0;

                ret = decode_inter_block(s, gb, quant_matrix, &skip, &map);
                if (ret < 0)
                    return ret;

                if (!map)
                    continue;
                s->idsp.idct_add(frame->data[plane] + (s->blocks_h - 1 - y) * 8 * frame->linesize[plane] + x * 8,
                                 frame->linesize[plane], s->block);
            }
        }
    }

    align_get_bits(gb);
    if (get_bits_left(gb) < 0)
        av_log(s->avctx, AV_LOG_WARNING, "overread\n");
    if (get_bits_left(gb) > 0)
        av_log(s->avctx, AV_LOG_WARNING, "underread: %d\n", get_bits_left(gb));

    return 0;
}