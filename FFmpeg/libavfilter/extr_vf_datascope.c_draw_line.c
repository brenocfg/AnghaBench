#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int width; int height; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_14__ {TYPE_3__* comp; } ;
struct TYPE_13__ {int nb_planes; int* pixelstep; int* vsub; int* hsub; TYPE_2__* desc; } ;
struct TYPE_12__ {int /*<<< orphan*/ * u16; int /*<<< orphan*/ * u8; } ;
struct TYPE_11__ {TYPE_1__* comp; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_4__ FFDrawContext ;
typedef  TYPE_5__ FFDrawColor ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int FFABS (int) ; 

__attribute__((used)) static void draw_line(FFDrawContext *draw, int x0, int y0, int x1, int y1,
                      AVFrame *out, FFDrawColor *color)
{
    int dx = FFABS(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = FFABS(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    int p, i;

    for (;;) {
        if (x0 >= 0 && y0 >= 0 && x0 < out->width && y0 < out->height) {
            for (p = 0; p < draw->nb_planes; p++) {
                if (draw->desc->comp[p].depth == 8) {
                    if (draw->nb_planes == 1) {
                        for (i = 0; i < 4; i++) {
                            out->data[0][y0 * out->linesize[0] + x0 * draw->pixelstep[0] + i] = color->comp[0].u8[i];
                        }
                    } else {
                        out->data[p][out->linesize[p] * (y0 >> draw->vsub[p]) + (x0 >> draw->hsub[p])] = color->comp[p].u8[0];
                    }
                } else {
                    if (draw->nb_planes == 1) {
                        for (i = 0; i < 4; i++) {
                            AV_WN16(out->data[0] + y0 * out->linesize[0] + 2 * (x0 * draw->pixelstep[0] + i), color->comp[0].u16[i]);
                        }
                    } else {
                        AV_WN16(out->data[p] + out->linesize[p] * (y0 >> draw->vsub[p]) + (x0 >> draw->hsub[p]) * 2, color->comp[p].u16[0]);
                    }
                }
            }
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 >-dx) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}