#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  (* op_pixels_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ;
struct TYPE_6__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ;} ;
struct TYPE_7__ {int mb_x; int mb_y; int width; int height; int uvlinesize; int h_edge_pos; int v_edge_pos; TYPE_2__ sc; TYPE_1__ vdsp; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 unsigned int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_clip (int,int,int) ; 
 int ff_h263_round_chroma (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void chroma_4mv_motion(MpegEncContext *s,
                              uint8_t *dest_cb, uint8_t *dest_cr,
                              uint8_t **ref_picture,
                              op_pixels_func *pix_op,
                              int mx, int my)
{
    uint8_t *ptr;
    int src_x, src_y, dxy, emu = 0;
    ptrdiff_t offset;

    /* In case of 8X8, we construct a single chroma motion vector
     * with a special rounding */
    mx = ff_h263_round_chroma(mx);
    my = ff_h263_round_chroma(my);

    dxy  = ((my & 1) << 1) | (mx & 1);
    mx >>= 1;
    my >>= 1;

    src_x = s->mb_x * 8 + mx;
    src_y = s->mb_y * 8 + my;
    src_x = av_clip(src_x, -8, (s->width >> 1));
    if (src_x == (s->width >> 1))
        dxy &= ~1;
    src_y = av_clip(src_y, -8, (s->height >> 1));
    if (src_y == (s->height >> 1))
        dxy &= ~2;

    offset = src_y * s->uvlinesize + src_x;
    ptr    = ref_picture[1] + offset;
    if ((unsigned)src_x >= FFMAX((s->h_edge_pos >> 1) - (dxy  & 1) - 7, 0) ||
        (unsigned)src_y >= FFMAX((s->v_edge_pos >> 1) - (dxy >> 1) - 7, 0)) {
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr,
                                 s->uvlinesize, s->uvlinesize,
                                 9, 9, src_x, src_y,
                                 s->h_edge_pos >> 1, s->v_edge_pos >> 1);
        ptr = s->sc.edge_emu_buffer;
        emu = 1;
    }
    pix_op[dxy](dest_cb, ptr, s->uvlinesize, 8);

    ptr = ref_picture[2] + offset;
    if (emu) {
        s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, ptr,
                                 s->uvlinesize, s->uvlinesize,
                                 9, 9, src_x, src_y,
                                 s->h_edge_pos >> 1, s->v_edge_pos >> 1);
        ptr = s->sc.edge_emu_buffer;
    }
    pix_op[dxy](dest_cr, ptr, s->uvlinesize, 8);
}