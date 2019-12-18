#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int size; float opacity; int flags; } ;
typedef  TYPE_1__ VectorscopeContext ;
struct TYPE_7__ {int* linesize; scalar_t__ height; scalar_t__ width; scalar_t__* data; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  draw_dots16 (int*,int,int const,float const) ; 
 int /*<<< orphan*/  draw_htext16 (TYPE_2__*,int,int,float const,int,int /*<<< orphan*/ ,int*) ; 
 int*** positions ; 
 int /*<<< orphan*/ * positions_name ; 

__attribute__((used)) static void color_graticule16(VectorscopeContext *s, AVFrame *out, int X, int Y, int D, int P)
{
    const int max = s->size - 1;
    const float o = s->opacity;
    int i;

    for (i = 0; i < 12; i++) {
        int x = positions[P][i][X];
        int y = positions[P][i][Y];
        int d = positions[P][i][D];

        draw_dots16((uint16_t *)(out->data[D] + y * out->linesize[D] + x * 2), out->linesize[D] / 2, d, o);
        draw_dots16((uint16_t *)(out->data[X] + y * out->linesize[X] + x * 2), out->linesize[X] / 2, x, o);
        draw_dots16((uint16_t *)(out->data[Y] + y * out->linesize[Y] + x * 2), out->linesize[Y] / 2, y, o);
        if (out->data[3])
            draw_dots16((uint16_t *)(out->data[3] + y * out->linesize[3] + x * 2), out->linesize[3] / 2, max, o);
    }

    if (s->flags & 1) {
        int x = positions[P][12][X];
        int y = positions[P][12][Y];
        int d = positions[P][12][D];

        draw_dots16((uint16_t *)(out->data[D] + y * out->linesize[D] + x * 2), out->linesize[D] / 2, d, o);
        draw_dots16((uint16_t *)(out->data[X] + y * out->linesize[X] + x * 2), out->linesize[X] / 2, x, o);
        draw_dots16((uint16_t *)(out->data[Y] + y * out->linesize[Y] + x * 2), out->linesize[Y] / 2, y, o);
        if (out->data[3])
            draw_dots16((uint16_t *)(out->data[3] + y * out->linesize[3] + x * 2), out->linesize[3] / 2, max, o);
    }

    if (s->flags & 2) {
        int x = positions[P][13][X];
        int y = positions[P][13][Y];
        int d = positions[P][13][D];

        draw_dots16((uint16_t *)(out->data[D] + y * out->linesize[D] + x * 2), out->linesize[D] / 2, d, o);
        draw_dots16((uint16_t *)(out->data[X] + y * out->linesize[X] + x * 2), out->linesize[X] / 2, x, o);
        draw_dots16((uint16_t *)(out->data[Y] + y * out->linesize[Y] + x * 2), out->linesize[Y] / 2, y, o);
        if (out->data[3])
            draw_dots16((uint16_t *)(out->data[3] + y * out->linesize[3] + x * 2), out->linesize[3] / 2, max, o);
    }

    for (i = 0; i < 6 && s->flags & 4; i++) {
        uint16_t color[4] = { 0, 0, 0, 0 };
        int x = positions[P][i][X];
        int y = positions[P][i][Y];
        int d = positions[P][i][D];

        color[D] = d;
        color[X] = x;
        color[Y] = y;
        color[3] = max;

        if (x > max / 2)
            x += 8;
        else
            x -= 14;
        if (y > max / 2)
            y += 8;
        else
            y -= 14;

        x = av_clip(x, 0, out->width - 9);
        y = av_clip(y, 0, out->height - 9);
        draw_htext16(out, x, y, o, 1. - o, positions_name[i], color);
    }
}