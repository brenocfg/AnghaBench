#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* dst; int /*<<< orphan*/  h; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int vsub; } ;
struct TYPE_8__ {int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ FlipContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *frame)
{
    FlipContext *flip = link->dst->priv;
    int i;

    for (i = 0; i < 4; i ++) {
        int vsub = i == 1 || i == 2 ? flip->vsub : 0;
        int height = AV_CEIL_RSHIFT(link->h, vsub);

        if (frame->data[i]) {
            frame->data[i] += (height - 1) * frame->linesize[i];
            frame->linesize[i] = -frame->linesize[i];
        }
    }

    return ff_filter_frame(link->dst->outputs[0], frame);
}