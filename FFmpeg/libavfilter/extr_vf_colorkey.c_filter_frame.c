#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * outputs; TYPE_1__* internal; TYPE_2__* priv; } ;
struct TYPE_16__ {TYPE_5__* dst; } ;
struct TYPE_15__ {int /*<<< orphan*/  height; } ;
struct TYPE_14__ {int /*<<< orphan*/  do_slice; } ;
struct TYPE_13__ {int (* execute ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ColorkeyContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_frame_make_writable (TYPE_3__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_5__*) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *frame)
{
    AVFilterContext *avctx = link->dst;
    ColorkeyContext *ctx = avctx->priv;
    int res;

    if (res = av_frame_make_writable(frame))
        return res;

    if (res = avctx->internal->execute(avctx, ctx->do_slice, frame, NULL, FFMIN(frame->height, ff_filter_get_nb_threads(avctx))))
        return res;

    return ff_filter_frame(avctx->outputs[0], frame);
}