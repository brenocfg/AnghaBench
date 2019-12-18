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
struct TYPE_13__ {int nb_planes; int flags; unsigned int* pixelstep; int* hsub; int* vsub; TYPE_2__* desc; } ;
struct TYPE_12__ {int /*<<< orphan*/ * u16; int /*<<< orphan*/ * u8; } ;
struct TYPE_11__ {int flags; TYPE_1__* comp; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_4__ FFDrawContext ;
typedef  TYPE_5__ FFDrawColor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int FF_DRAW_PROCESS_ALPHA ; 
 int /*<<< orphan*/  blend_line_hv (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  blend_line_hv16 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  clip_interval (int,int*,int*,int*) ; 
 int /*<<< orphan*/  component_used (TYPE_4__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * pointer_at (TYPE_4__*,int /*<<< orphan*/ **,int*,unsigned int,int,int) ; 
 int /*<<< orphan*/  subsampling_bounds (int,int*,int*,int*,int*) ; 

void ff_blend_mask(FFDrawContext *draw, FFDrawColor *color,
                   uint8_t *dst[], int dst_linesize[], int dst_w, int dst_h,
                   const uint8_t *mask,  int mask_linesize, int mask_w, int mask_h,
                   int l2depth, unsigned endianness, int x0, int y0)
{
    unsigned alpha, nb_planes, nb_comp, plane, comp;
    int xm0, ym0, w_sub, h_sub, x_sub, y_sub, left, right, top, bottom, y;
    uint8_t *p0, *p;
    const uint8_t *m;

    clip_interval(dst_w, &x0, &mask_w, &xm0);
    clip_interval(dst_h, &y0, &mask_h, &ym0);
    mask += ym0 * mask_linesize;
    if (mask_w <= 0 || mask_h <= 0 || !color->rgba[3])
        return;
    if (draw->desc->comp[0].depth <= 8) {
        /* alpha is in the [ 0 ; 0x10203 ] range,
           alpha * mask is in the [ 0 ; 0x1010101 - 4 ] range */
        alpha = (0x10307 * color->rgba[3] + 0x3) >> 8;
    } else {
        alpha = (0x101 * color->rgba[3] + 0x2) >> 8;
    }
    nb_planes = draw->nb_planes - !!(draw->desc->flags & AV_PIX_FMT_FLAG_ALPHA && !(draw->flags & FF_DRAW_PROCESS_ALPHA));
    nb_planes += !nb_planes;
    for (plane = 0; plane < nb_planes; plane++) {
        nb_comp = draw->pixelstep[plane];
        p0 = pointer_at(draw, dst, dst_linesize, plane, x0, y0);
        w_sub = mask_w;
        h_sub = mask_h;
        x_sub = x0;
        y_sub = y0;
        subsampling_bounds(draw->hsub[plane], &x_sub, &w_sub, &left, &right);
        subsampling_bounds(draw->vsub[plane], &y_sub, &h_sub, &top, &bottom);
        for (comp = 0; comp < nb_comp; comp++) {
            const int depth = draw->desc->comp[comp].depth;

            if (!component_used(draw, plane, comp))
                continue;
            p = p0 + comp;
            m = mask;
            if (top) {
                if (depth <= 8) {
                    blend_line_hv(p, draw->pixelstep[plane],
                                  color->comp[plane].u8[comp], alpha,
                                  m, mask_linesize, l2depth, w_sub,
                                  draw->hsub[plane], draw->vsub[plane],
                                  xm0, left, right, top);
                } else {
                    blend_line_hv16(p, draw->pixelstep[plane],
                                    color->comp[plane].u16[comp], alpha,
                                    m, mask_linesize, l2depth, w_sub,
                                    draw->hsub[plane], draw->vsub[plane],
                                    xm0, left, right, top);
                }
                p += dst_linesize[plane];
                m += top * mask_linesize;
            }
            if (depth <= 8) {
                for (y = 0; y < h_sub; y++) {
                    blend_line_hv(p, draw->pixelstep[plane],
                                  color->comp[plane].u8[comp], alpha,
                                  m, mask_linesize, l2depth, w_sub,
                                  draw->hsub[plane], draw->vsub[plane],
                                  xm0, left, right, 1 << draw->vsub[plane]);
                    p += dst_linesize[plane];
                    m += mask_linesize << draw->vsub[plane];
                }
            } else {
                for (y = 0; y < h_sub; y++) {
                    blend_line_hv16(p, draw->pixelstep[plane],
                                    color->comp[plane].u16[comp], alpha,
                                    m, mask_linesize, l2depth, w_sub,
                                    draw->hsub[plane], draw->vsub[plane],
                                    xm0, left, right, 1 << draw->vsub[plane]);
                    p += dst_linesize[plane];
                    m += mask_linesize << draw->vsub[plane];
                }
            }
            if (bottom) {
                if (depth <= 8) {
                    blend_line_hv(p, draw->pixelstep[plane],
                                  color->comp[plane].u8[comp], alpha,
                                  m, mask_linesize, l2depth, w_sub,
                                  draw->hsub[plane], draw->vsub[plane],
                                  xm0, left, right, bottom);
                } else {
                    blend_line_hv16(p, draw->pixelstep[plane],
                                    color->comp[plane].u16[comp], alpha,
                                    m, mask_linesize, l2depth, w_sub,
                                    draw->hsub[plane], draw->vsub[plane],
                                    xm0, left, right, bottom);
                }
            }
        }
    }
}