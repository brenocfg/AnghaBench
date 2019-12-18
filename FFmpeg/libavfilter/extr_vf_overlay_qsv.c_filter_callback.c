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
struct TYPE_14__ {int /*<<< orphan*/  time_base; TYPE_1__* src; } ;
struct TYPE_13__ {int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_12__ {TYPE_2__ fs; } ;
struct TYPE_10__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ QSVOverlayContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static int filter_callback(AVFilterLink *outlink, AVFrame *frame)
{
    QSVOverlayContext *s = outlink->src->priv;
    frame->pts = av_rescale_q(s->fs.pts,
                              s->fs.time_base, outlink->time_base);
    return ff_filter_frame(outlink, frame);
}