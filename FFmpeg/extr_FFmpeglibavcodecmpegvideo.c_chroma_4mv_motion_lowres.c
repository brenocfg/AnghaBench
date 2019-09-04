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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  (* h264_chroma_mc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ;
struct TYPE_8__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int const,int const) ;} ;
struct TYPE_9__ {int const h_edge_pos; int const v_edge_pos; int const mb_x; int const mb_y; int uvlinesize; TYPE_3__ sc; TYPE_2__ vdsp; scalar_t__ quarter_sample; TYPE_1__* avctx; } ;
struct TYPE_6__ {int lowres; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 unsigned int FFMAX (int const,int /*<<< orphan*/ ) ; 
 int FFMIN (int const,int) ; 
 int ff_h263_round_chroma (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int const,int const) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int const,int const) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int const,int,int) ; 

__attribute__((used)) static inline void chroma_4mv_motion_lowres(MpegEncContext *s,
                                            uint8_t *dest_cb, uint8_t *dest_cr,
                                            uint8_t **ref_picture,
                                            h264_chroma_mc_func * pix_op,
                                            int mx, int my)
{
    const int lowres     = s->avctx->lowres;
    const int op_index   = FFMIN(lowres, 3);
    const int block_s    = 8 >> lowres;
    const int s_mask     = (2 << lowres) - 1;
    const int h_edge_pos = s->h_edge_pos >> lowres + 1;
    const int v_edge_pos = s->v_edge_pos >> lowres + 1;
    int emu = 0, src_x, src_y, sx, sy;
    ptrdiff_t offset;
    uint8_t *ptr;

    if (s->quarter_sample) {
        mx /= 2;
        my /= 2;
    }

    /* In case of 8X8, we construct a single chroma motion vector
       with a special rounding */
    mx = ff_h263_round_chroma(mx);
    my = ff_h263_round_chroma(my);

    sx = mx & s_mask;
    sy = my & s_mask;
    src_x = s->mb_x * block_s + (mx >> lowres + 1);
    src_y = s->mb_y * block_s + (my >> lowres + 1);

    offset = src_y * s->uvlinesize + src_x;
    ptr = ref_picture[1] + offset;
    if ((unsigned) src_x > FFMAX(h_edge_pos - (!!sx) - block_s, 0) ||
        (unsigned) src_y > FFMAX(v_edge_pos - (!!sy) - block_s, 0)) {
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr,
                                 s->uvlinesize, s->uvlinesize,
                                 9, 9,
                                 src_x, src_y, h_edge_pos, v_edge_pos);
        ptr = s->sc.edge_emu_buffer;
        emu = 1;
    }
    sx = (sx << 2) >> lowres;
    sy = (sy << 2) >> lowres;
    pix_op[op_index](dest_cb, ptr, s->uvlinesize, block_s, sx, sy);

    ptr = ref_picture[2] + offset;
    if (emu) {
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr,
                                 s->uvlinesize, s->uvlinesize,
                                 9, 9,
                                 src_x, src_y, h_edge_pos, v_edge_pos);
        ptr = s->sc.edge_emu_buffer;
    }
    pix_op[op_index](dest_cr, ptr, s->uvlinesize, block_s, sx, sy);
}