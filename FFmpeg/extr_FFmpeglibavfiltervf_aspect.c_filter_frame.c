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
struct TYPE_11__ {TYPE_1__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_9__ {int /*<<< orphan*/  sar; } ;
struct TYPE_8__ {int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ AspectContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *frame)
{
    AspectContext *s = link->dst->priv;

    frame->sample_aspect_ratio = s->sar;
    return ff_filter_frame(link->dst->outputs[0], frame);
}