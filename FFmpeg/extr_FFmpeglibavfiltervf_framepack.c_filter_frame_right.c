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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** input_views; } ;
typedef  TYPE_1__ FramepackContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 size_t RIGHT ; 
 int try_push_frame (TYPE_3__*) ; 

__attribute__((used)) static int filter_frame_right(AVFilterLink *inlink, AVFrame *frame)
{
    FramepackContext *s = inlink->dst->priv;
    s->input_views[RIGHT] = frame;
    return try_push_frame(inlink->dst);
}