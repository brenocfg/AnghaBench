#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* dst; } ;
struct TYPE_12__ {int width; int height; int* linesize; scalar_t__* data; } ;
struct TYPE_10__ {int* hsub; int* vsub; int* pixelstep; } ;
struct TYPE_11__ {scalar_t__ inlink_w; int x; int y; TYPE_2__ draw; scalar_t__ in_h; scalar_t__ h; scalar_t__ in_w; scalar_t__ w; } ;
struct TYPE_9__ {int /*<<< orphan*/ * outputs; TYPE_3__* priv; } ;
typedef  TYPE_3__ PadContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 TYPE_4__* ff_get_video_buffer (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static AVFrame *get_video_buffer(AVFilterLink *inlink, int w, int h)
{
    PadContext *s = inlink->dst->priv;
    AVFrame *frame;
    int plane;

    if (s->inlink_w <= 0)
        return NULL;

    frame = ff_get_video_buffer(inlink->dst->outputs[0],
                                w + (s->w - s->in_w),
                                h + (s->h - s->in_h) + (s->x > 0));

    if (!frame)
        return NULL;

    frame->width  = w;
    frame->height = h;

    for (plane = 0; plane < 4 && frame->data[plane] && frame->linesize[plane]; plane++) {
        int hsub = s->draw.hsub[plane];
        int vsub = s->draw.vsub[plane];
        frame->data[plane] += (s->x >> hsub) * s->draw.pixelstep[plane] +
                              (s->y >> vsub) * frame->linesize[plane];
    }

    return frame;
}