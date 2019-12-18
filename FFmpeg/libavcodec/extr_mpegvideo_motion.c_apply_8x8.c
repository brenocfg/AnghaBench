#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  (* qpel_mc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;
typedef  int /*<<< orphan*/  op_pixels_func ;
struct TYPE_9__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ;} ;
struct TYPE_11__ {int mb_x; int mb_y; int*** mv; int width; int height; int linesize; int h_edge_pos; int v_edge_pos; TYPE_3__* avctx; TYPE_2__ sc; TYPE_1__ vdsp; scalar_t__ quarter_sample; } ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  CONFIG_GRAY ; 
 unsigned int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  chroma_4mv_motion (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hpel_motion (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void apply_8x8(MpegEncContext *s,
                             uint8_t *dest_y,
                             uint8_t *dest_cb,
                             uint8_t *dest_cr,
                             int dir,
                             uint8_t **ref_picture,
                             qpel_mc_func (*qpix_op)[16],
                             op_pixels_func (*pix_op)[4])
{
    int dxy, mx, my, src_x, src_y;
    int i;
    int mb_x = s->mb_x;
    int mb_y = s->mb_y;
    uint8_t *ptr, *dest;

    mx = 0;
    my = 0;
    if (s->quarter_sample) {
        for (i = 0; i < 4; i++) {
            int motion_x = s->mv[dir][i][0];
            int motion_y = s->mv[dir][i][1];

            dxy   = ((motion_y & 3) << 2) | (motion_x & 3);
            src_x = mb_x * 16 + (motion_x >> 2) + (i & 1) * 8;
            src_y = mb_y * 16 + (motion_y >> 2) + (i >> 1) * 8;

            /* WARNING: do no forget half pels */
            src_x = av_clip(src_x, -16, s->width);
            if (src_x == s->width)
                dxy &= ~3;
            src_y = av_clip(src_y, -16, s->height);
            if (src_y == s->height)
                dxy &= ~12;

            ptr = ref_picture[0] + (src_y * s->linesize) + (src_x);
            if ((unsigned)src_x >= FFMAX(s->h_edge_pos - (motion_x & 3) - 7, 0) ||
                (unsigned)src_y >= FFMAX(s->v_edge_pos - (motion_y & 3) - 7, 0)) {
                s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr,
                                         s->linesize, s->linesize,
                                         9, 9,
                                         src_x, src_y,
                                         s->h_edge_pos,
                                         s->v_edge_pos);
                ptr = s->sc.edge_emu_buffer;
            }
            dest = dest_y + ((i & 1) * 8) + (i >> 1) * 8 * s->linesize;
            qpix_op[1][dxy](dest, ptr, s->linesize);

            mx += s->mv[dir][i][0] / 2;
            my += s->mv[dir][i][1] / 2;
        }
    } else {
        for (i = 0; i < 4; i++) {
            hpel_motion(s,
                        dest_y + ((i & 1) * 8) + (i >> 1) * 8 * s->linesize,
                        ref_picture[0],
                        mb_x * 16 + (i & 1) * 8,
                        mb_y * 16 + (i >> 1) * 8,
                        pix_op[1],
                        s->mv[dir][i][0],
                        s->mv[dir][i][1]);

            mx += s->mv[dir][i][0];
            my += s->mv[dir][i][1];
        }
    }

    if (!CONFIG_GRAY || !(s->avctx->flags & AV_CODEC_FLAG_GRAY))
        chroma_4mv_motion(s, dest_cb, dest_cr,
                          ref_picture, pix_op[1], mx, my);
}