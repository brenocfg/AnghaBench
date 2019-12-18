#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int* rgba; TYPE_3__* comp; } ;
struct TYPE_13__ {int nb_planes; int flags; unsigned int* pixelstep; int /*<<< orphan*/ * hsub; TYPE_2__* desc; int /*<<< orphan*/ * vsub; } ;
struct TYPE_12__ {int /*<<< orphan*/ * u16; int /*<<< orphan*/ * u8; } ;
struct TYPE_11__ {int flags; TYPE_1__* comp; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_4__ FFDrawContext ;
typedef  TYPE_5__ FFDrawColor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int FF_DRAW_PROCESS_ALPHA ; 
 int /*<<< orphan*/  blend_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  blend_line16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clip_interval (int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  component_used (TYPE_4__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * pointer_at (TYPE_4__*,int /*<<< orphan*/ **,int*,unsigned int,int,int) ; 
 int /*<<< orphan*/  subsampling_bounds (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 

void ff_blend_rectangle(FFDrawContext *draw, FFDrawColor *color,
                        uint8_t *dst[], int dst_linesize[],
                        int dst_w, int dst_h,
                        int x0, int y0, int w, int h)
{
    unsigned alpha, nb_planes, nb_comp, plane, comp;
    int w_sub, h_sub, x_sub, y_sub, left, right, top, bottom, y;
    uint8_t *p0, *p;

    /* TODO optimize if alpha = 0xFF */
    clip_interval(dst_w, &x0, &w, NULL);
    clip_interval(dst_h, &y0, &h, NULL);
    if (w <= 0 || h <= 0 || !color->rgba[3])
        return;
    if (draw->desc->comp[0].depth <= 8) {
        /* 0x10203 * alpha + 2 is in the [ 2 ; 0x1010101 - 2 ] range */
        alpha = 0x10203 * color->rgba[3] + 0x2;
    } else {
        /* 0x101 * alpha is in the [ 2 ; 0x1001] range */
        alpha = 0x101 * color->rgba[3] + 0x2;
    }
    nb_planes = draw->nb_planes - !!(draw->desc->flags & AV_PIX_FMT_FLAG_ALPHA && !(draw->flags & FF_DRAW_PROCESS_ALPHA));
    nb_planes += !nb_planes;
    for (plane = 0; plane < nb_planes; plane++) {
        nb_comp = draw->pixelstep[plane];
        p0 = pointer_at(draw, dst, dst_linesize, plane, x0, y0);
        w_sub = w;
        h_sub = h;
        x_sub = x0;
        y_sub = y0;
        subsampling_bounds(draw->hsub[plane], &x_sub, &w_sub, &left, &right);
        subsampling_bounds(draw->vsub[plane], &y_sub, &h_sub, &top, &bottom);
        for (comp = 0; comp < nb_comp; comp++) {
            const int depth = draw->desc->comp[comp].depth;

            if (!component_used(draw, plane, comp))
                continue;
            p = p0 + comp;
            if (top) {
                if (depth <= 8) {
                    blend_line(p, color->comp[plane].u8[comp], alpha >> 1,
                               draw->pixelstep[plane], w_sub,
                               draw->hsub[plane], left, right);
                } else {
                    blend_line16(p, color->comp[plane].u16[comp], alpha >> 1,
                                 draw->pixelstep[plane], w_sub,
                                 draw->hsub[plane], left, right);
                }
                p += dst_linesize[plane];
            }
            if (depth <= 8) {
                for (y = 0; y < h_sub; y++) {
                    blend_line(p, color->comp[plane].u8[comp], alpha,
                               draw->pixelstep[plane], w_sub,
                               draw->hsub[plane], left, right);
                    p += dst_linesize[plane];
                }
            } else {
                for (y = 0; y < h_sub; y++) {
                    blend_line16(p, color->comp[plane].u16[comp], alpha,
                                 draw->pixelstep[plane], w_sub,
                                 draw->hsub[plane], left, right);
                    p += dst_linesize[plane];
                }
            }
            if (bottom) {
                if (depth <= 8) {
                    blend_line(p, color->comp[plane].u8[comp], alpha >> 1,
                               draw->pixelstep[plane], w_sub,
                               draw->hsub[plane], left, right);
                } else {
                    blend_line16(p, color->comp[plane].u16[comp], alpha >> 1,
                                 draw->pixelstep[plane], w_sub,
                                 draw->hsub[plane], left, right);
                }
            }
        }
    }
}