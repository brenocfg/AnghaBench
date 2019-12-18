#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int linesize; size_t mb_x; size_t mb_stride; scalar_t__ mb_y; scalar_t__ start_mb_y; int uvlinesize; int end_mb_y; int mb_width; int /*<<< orphan*/ ** dest; scalar_t__ first_slice_line; TYPE_1__* avctx; } ;
struct TYPE_8__ {int* cbp; int* ttblk; TYPE_3__ s; } ;
typedef  TYPE_2__ VC1Context ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int BOTTOM_EDGE ; 
 scalar_t__ CONFIG_GRAY ; 
 int LEFT_EDGE ; 
 int RIGHT_EDGE ; 
 int TOP_EDGE ; 
 int /*<<< orphan*/  vc1_b_h_intfi_loop_filter (TYPE_2__*,int /*<<< orphan*/ *,int*,int*,int,int) ; 
 int /*<<< orphan*/  vc1_b_v_intfi_loop_filter (TYPE_2__*,int /*<<< orphan*/ *,int*,int*,int,int) ; 

void ff_vc1_b_intfi_loop_filter(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    int block_count = CONFIG_GRAY && (s->avctx->flags & AV_CODEC_FLAG_GRAY) ? 4 : 6;
    uint8_t *dest;
    uint32_t *cbp;
    int *ttblk;
    uint32_t flags = 0;
    int i;

    /* Within a MB, the vertical loop filter always runs before the horizontal.
     * To accomplish that, we run the V loop filter on all applicable
     * horizontal borders of the MB above the currently decoded MB. Then,
     * we wait for the next loop filter iteration to do H loop filter on all
     * applicable vertical borders of this MB. Therefore, the loop filter
     * trails by one row and one column relative to the decoding loop. */
    if (!s->first_slice_line) {
        dest = s->dest[0] - 16 * s->linesize;
        cbp = &v->cbp[s->mb_x - s->mb_stride];
        ttblk = &v->ttblk[s->mb_x - s->mb_stride];
        flags = s->mb_y == s->start_mb_y + 1 ? TOP_EDGE : 0;
        for (i = 0; i < block_count; i++)
            vc1_b_v_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest, cbp, ttblk, flags, i);
    }
    if (s->mb_y == s->end_mb_y - 1) {
        dest = s->dest[0];
        cbp = &v->cbp[s->mb_x];
        ttblk = &v->ttblk[s->mb_x];
        flags = s->first_slice_line ? TOP_EDGE | BOTTOM_EDGE : BOTTOM_EDGE;
        for (i = 0; i < block_count; i++)
            vc1_b_v_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] : dest, cbp, ttblk, flags, i);
    }

    if (!s->first_slice_line) {
        dest = s->dest[0] - 16 * s->linesize - 16;
        cbp = &v->cbp[s->mb_x - s->mb_stride - 1];
        ttblk = &v->ttblk[s->mb_x - s->mb_stride - 1];
        if (s->mb_x) {
            flags = s->mb_x == 1 ? LEFT_EDGE : 0;
            for (i = 0; i < block_count; i++)
                vc1_b_h_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize - 8 : dest, cbp, ttblk, flags, i);
        }
        if (s->mb_x == s->mb_width - 1) {
            dest += 16;
            cbp++;
            ttblk++;
            flags = s->mb_x == 0 ? LEFT_EDGE | RIGHT_EDGE : RIGHT_EDGE;
            for (i = 0; i < block_count; i++)
                vc1_b_h_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] - 8 * s->uvlinesize : dest, cbp, ttblk, flags, i);
        }
    }
    if (s->mb_y == s->end_mb_y - 1) {
        dest = s->dest[0] - 16;
        cbp = &v->cbp[s->mb_x - 1];
        ttblk = &v->ttblk[s->mb_x - 1];
        if (s->mb_x) {
            flags = s->mb_x == 1 ? LEFT_EDGE : 0;
            for (i = 0; i < block_count; i++)
                vc1_b_h_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] - 8 : dest, cbp, ttblk, flags, i);
        }
        if (s->mb_x == s->mb_width - 1) {
            dest += 16;
            cbp++;
            ttblk++;
            flags = s->mb_x == 0 ? LEFT_EDGE | RIGHT_EDGE : RIGHT_EDGE;
            for (i = 0; i < block_count; i++)
                vc1_b_h_intfi_loop_filter(v, i > 3 ? s->dest[i - 3] : dest, cbp, ttblk, flags, i);
        }
    }
}