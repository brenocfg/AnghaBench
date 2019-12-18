#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int nb_planes; int* pixelstep; TYPE_4__* desc; } ;
struct TYPE_19__ {int width; int height; int** data; int* linesize; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {TYPE_1__ member_0; } ;
struct TYPE_17__ {size_t nb_values; int max; TYPE_8__ draw; scalar_t__ scope; TYPE_2__* values; int /*<<< orphan*/  (* pick_color ) (TYPE_8__*,TYPE_6__*,TYPE_7__*,int,int,int*) ;} ;
struct TYPE_16__ {TYPE_3__* comp; } ;
struct TYPE_15__ {int depth; } ;
struct TYPE_14__ {int* p; } ;
typedef  int /*<<< orphan*/  PixelValues ;
typedef  TYPE_5__ OscilloscopeContext ;
typedef  TYPE_6__ FFDrawColor ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN16 (int*,int) ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,TYPE_6__*,TYPE_7__*,int,int,int*) ; 

__attribute__((used)) static void draw_scope(OscilloscopeContext *s, int x0, int y0, int x1, int y1,
                       AVFrame *out, PixelValues *p, int state)
{
    int dx = FFABS(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = FFABS(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {
        if (x0 >= 0 && y0 >= 0 && x0 < out->width && y0 < out->height) {
            FFDrawColor color = { { 0 } };
            int value[4] = { 0 };

            s->pick_color(&s->draw, &color, out, x0, y0, value);
            s->values[s->nb_values].p[0] = value[0];
            s->values[s->nb_values].p[1] = value[1];
            s->values[s->nb_values].p[2] = value[2];
            s->values[s->nb_values].p[3] = value[3];
            s->nb_values++;

            if (s->scope) {
                if (s->draw.desc->comp[0].depth == 8) {
                    if (s->draw.nb_planes == 1) {
                        int i;

                        for (i = 0; i < s->draw.pixelstep[0]; i++)
                            out->data[0][out->linesize[0] * y0 + x0 * s->draw.pixelstep[0] + i] = 255 * ((s->nb_values + state) & 1);
                    } else {
                        out->data[0][out->linesize[0] * y0 + x0] = 255 * ((s->nb_values + state) & 1);
                    }
                } else {
                    if (s->draw.nb_planes == 1) {
                        int i;

                        for (i = 0; i < s->draw.pixelstep[0]; i++)
                            AV_WN16(out->data[0] + out->linesize[0] * y0 + 2 * x0 * (s->draw.pixelstep[0] + i), (s->max - 1) * ((s->nb_values + state) & 1));
                    } else {
                        AV_WN16(out->data[0] + out->linesize[0] * y0 + 2 * x0, (s->max - 1) * ((s->nb_values + state) & 1));
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