#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* dst; } ;
struct TYPE_11__ {int height; unsigned char** data; int* linesize; int width; } ;
struct TYPE_10__ {int x; int y; int h; int vsub; int w; unsigned char* yuv_color; int hsub; scalar_t__ invert_color; scalar_t__ replace; scalar_t__ have_alpha; } ;
struct TYPE_9__ {int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ DrawBoxContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 size_t A ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 size_t U ; 
 size_t V ; 
 size_t Y ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ pixel_belongs_to_box (TYPE_2__*,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    DrawBoxContext *s = inlink->dst->priv;
    int plane, x, y, xb = s->x, yb = s->y;
    unsigned char *row[4];

    if (s->have_alpha && s->replace) {
        for (y = FFMAX(yb, 0); y < frame->height && y < (yb + s->h); y++) {
            row[0] = frame->data[0] + y * frame->linesize[0];
            row[3] = frame->data[3] + y * frame->linesize[3];

            for (plane = 1; plane < 3; plane++)
                row[plane] = frame->data[plane] +
                     frame->linesize[plane] * (y >> s->vsub);

            if (s->invert_color) {
                for (x = FFMAX(xb, 0); x < xb + s->w && x < frame->width; x++)
                    if (pixel_belongs_to_box(s, x, y))
                        row[0][x] = 0xff - row[0][x];
            } else {
                for (x = FFMAX(xb, 0); x < xb + s->w && x < frame->width; x++) {
                    if (pixel_belongs_to_box(s, x, y)) {
                        row[0][x           ] = s->yuv_color[Y];
                        row[1][x >> s->hsub] = s->yuv_color[U];
                        row[2][x >> s->hsub] = s->yuv_color[V];
                        row[3][x           ] = s->yuv_color[A];
                    }
                }
            }
        }
    } else {
        for (y = FFMAX(yb, 0); y < frame->height && y < (yb + s->h); y++) {
            row[0] = frame->data[0] + y * frame->linesize[0];

            for (plane = 1; plane < 3; plane++)
                row[plane] = frame->data[plane] +
                     frame->linesize[plane] * (y >> s->vsub);

            if (s->invert_color) {
                for (x = FFMAX(xb, 0); x < xb + s->w && x < frame->width; x++)
                    if (pixel_belongs_to_box(s, x, y))
                        row[0][x] = 0xff - row[0][x];
            } else {
                for (x = FFMAX(xb, 0); x < xb + s->w && x < frame->width; x++) {
                    double alpha = (double)s->yuv_color[A] / 255;

                    if (pixel_belongs_to_box(s, x, y)) {
                        row[0][x                 ] = (1 - alpha) * row[0][x                 ] + alpha * s->yuv_color[Y];
                        row[1][x >> s->hsub] = (1 - alpha) * row[1][x >> s->hsub] + alpha * s->yuv_color[U];
                        row[2][x >> s->hsub] = (1 - alpha) * row[2][x >> s->hsub] + alpha * s->yuv_color[V];
                    }
                }
            }
        }
    }

    return ff_filter_frame(inlink->dst->outputs[0], frame);
}