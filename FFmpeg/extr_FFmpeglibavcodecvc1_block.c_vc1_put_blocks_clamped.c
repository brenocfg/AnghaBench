#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* put_pixels_clamped ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* put_signed_pixels_clamped ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_9__ {int mb_x; int* block_index; int* block_wrap; int linesize; int uvlinesize; int mb_y; int end_mb_y; int mb_stride; int /*<<< orphan*/ ** dest; TYPE_1__ idsp; int /*<<< orphan*/  first_slice_line; TYPE_2__* avctx; } ;
struct TYPE_8__ {scalar_t__ fcm; size_t topleft_blk_idx; int end_mb_x; size_t top_blk_idx; int* fieldtx_plane; size_t left_blk_idx; size_t cur_blk_idx; int /*<<< orphan*/ ** block; scalar_t__** mb_type; TYPE_4__ s; } ;
typedef  TYPE_3__ VC1Context ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ CONFIG_GRAY ; 
 scalar_t__ ILACE_FRAME ; 
 size_t* block_map ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vc1_put_blocks_clamped(VC1Context *v, int put_signed)
{
    MpegEncContext *s = &v->s;
    uint8_t *dest;
    int block_count = CONFIG_GRAY && (s->avctx->flags & AV_CODEC_FLAG_GRAY) ? 4 : 6;
    int fieldtx = 0;
    int i;

    /* The put pixels loop is one MB row and one MB column behind the decoding
     * loop because we can only put pixels when overlap filtering is done. For
     * interlaced frame pictures, however, the put pixels loop is only one
     * column behind the decoding loop as interlaced frame pictures only need
     * horizontal overlap filtering. */
    if (!s->first_slice_line && v->fcm != ILACE_FRAME) {
        if (s->mb_x) {
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - s->block_wrap[i] - 1] :
                            v->mb_type[0][s->block_index[i] - 2 * s->block_wrap[i] - 2]) {
                    dest = s->dest[0] + ((i & 2) - 4) * 4 * s->linesize + ((i & 1) - 2) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->topleft_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize - 8 : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->topleft_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize - 8 : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize);
                }
            }
        }
        if (s->mb_x == v->end_mb_x - 1) {
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - s->block_wrap[i]] :
                            v->mb_type[0][s->block_index[i] - 2 * s->block_wrap[i]]) {
                    dest = s->dest[0] + ((i & 2) - 4) * 4 * s->linesize + (i & 1) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->top_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->top_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize);
                }
            }
        }
    }
    if (s->mb_y == s->end_mb_y - 1 || v->fcm == ILACE_FRAME) {
        if (s->mb_x) {
            if (v->fcm == ILACE_FRAME)
                fieldtx = v->fieldtx_plane[s->mb_y * s->mb_stride + s->mb_x - 1];
            for (i = 0; i < block_count; i++) {
                if (i > 3 ? v->mb_type[0][s->block_index[i] - 1] :
                            v->mb_type[0][s->block_index[i] - 2]) {
                    if (fieldtx)
                        dest = s->dest[0] + ((i & 2) >> 1) * s->linesize + ((i & 1) - 2) * 8;
                    else
                        dest = s->dest[0] + (i & 2) * 4 * s->linesize + ((i & 1) - 2) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->left_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] - 8 : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->left_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] - 8 : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                }
            }
        }
        if (s->mb_x == v->end_mb_x - 1) {
            if (v->fcm == ILACE_FRAME)
                fieldtx = v->fieldtx_plane[s->mb_y * s->mb_stride + s->mb_x];
            for (i = 0; i < block_count; i++) {
                if (v->mb_type[0][s->block_index[i]]) {
                    if (fieldtx)
                        dest = s->dest[0] + ((i & 2) >> 1) * s->linesize + (i & 1) * 8;
                    else
                        dest = s->dest[0] + (i & 2) * 4 * s->linesize + (i & 1) * 8;
                    if (put_signed)
                        s->idsp.put_signed_pixels_clamped(v->block[v->cur_blk_idx][block_map[i]],
                                                          i > 3 ? s->dest[i - 3] : dest,
                                                          i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                    else
                        s->idsp.put_pixels_clamped(v->block[v->cur_blk_idx][block_map[i]],
                                                   i > 3 ? s->dest[i - 3] : dest,
                                                   i > 3 ? s->uvlinesize : s->linesize << fieldtx);
                }
            }
        }
    }
}