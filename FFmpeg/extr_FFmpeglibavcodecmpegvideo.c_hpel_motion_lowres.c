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
typedef  int /*<<< orphan*/  (* h264_chroma_mc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ;
struct TYPE_8__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  linesize; TYPE_3__ sc; TYPE_2__ vdsp; scalar_t__ quarter_sample; TYPE_1__* avctx; } ;
struct TYPE_6__ {int lowres; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 unsigned int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int const,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static inline int hpel_motion_lowres(MpegEncContext *s,
                                     uint8_t *dest, uint8_t *src,
                                     int field_based, int field_select,
                                     int src_x, int src_y,
                                     int width, int height, ptrdiff_t stride,
                                     int h_edge_pos, int v_edge_pos,
                                     int w, int h, h264_chroma_mc_func *pix_op,
                                     int motion_x, int motion_y)
{
    const int lowres   = s->avctx->lowres;
    const int op_index = FFMIN(lowres, 3);
    const int s_mask   = (2 << lowres) - 1;
    int emu = 0;
    int sx, sy;

    if (s->quarter_sample) {
        motion_x /= 2;
        motion_y /= 2;
    }

    sx = motion_x & s_mask;
    sy = motion_y & s_mask;
    src_x += motion_x >> lowres + 1;
    src_y += motion_y >> lowres + 1;

    src   += src_y * stride + src_x;

    if ((unsigned)src_x > FFMAX( h_edge_pos - (!!sx) - w,                 0) ||
        (unsigned)src_y > FFMAX((v_edge_pos >> field_based) - (!!sy) - h, 0)) {
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, src,
                                 s->linesize, s->linesize,
                                 w + 1, (h + 1) << field_based,
                                 src_x, src_y   << field_based,
                                 h_edge_pos, v_edge_pos);
        src = s->sc.edge_emu_buffer;
        emu = 1;
    }

    sx = (sx << 2) >> lowres;
    sy = (sy << 2) >> lowres;
    if (field_select)
        src += s->linesize;
    pix_op[op_index](dest, src, stride, h, sx, sy);
    return emu;
}