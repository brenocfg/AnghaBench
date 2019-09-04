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
typedef  int /*<<< orphan*/  (* op_pixels_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ;
struct TYPE_6__ {int /*<<< orphan*/ * edge_emu_buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* emulated_edge_mc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ;} ;
struct TYPE_7__ {int width; int height; int linesize; int h_edge_pos; int v_edge_pos; TYPE_2__ sc; TYPE_1__ vdsp; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 unsigned int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int hpel_motion(MpegEncContext *s,
                              uint8_t *dest, uint8_t *src,
                              int src_x, int src_y,
                              op_pixels_func *pix_op,
                              int motion_x, int motion_y)
{
    int dxy = 0;
    int emu = 0;

    src_x += motion_x >> 1;
    src_y += motion_y >> 1;

    /* WARNING: do no forget half pels */
    src_x = av_clip(src_x, -16, s->width); // FIXME unneeded for emu?
    if (src_x != s->width)
        dxy |= motion_x & 1;
    src_y = av_clip(src_y, -16, s->height);
    if (src_y != s->height)
        dxy |= (motion_y & 1) << 1;
    src += src_y * s->linesize + src_x;

        if ((unsigned)src_x >= FFMAX(s->h_edge_pos - (motion_x & 1) - 7, 0) ||
            (unsigned)src_y >= FFMAX(s->v_edge_pos - (motion_y & 1) - 7, 0)) {
            s->vdsp.emulated_edge_mc(s->sc.edge_emu_buffer, src,
                                     s->linesize, s->linesize,
                                     9, 9,
                                     src_x, src_y,
                                     s->h_edge_pos, s->v_edge_pos);
            src = s->sc.edge_emu_buffer;
            emu = 1;
        }
    pix_op[dxy](dest, src, s->linesize, 8);
    return emu;
}