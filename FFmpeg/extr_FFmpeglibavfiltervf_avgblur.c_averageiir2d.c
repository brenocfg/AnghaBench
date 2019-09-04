#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int width; int height; int /*<<< orphan*/  linesize; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_18__ {TYPE_1__* internal; TYPE_3__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int* planewidth; int* planeheight; int /*<<< orphan*/  filter_vertically; int /*<<< orphan*/  filter_horizontally; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* execute ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ AverageBlurContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int const,int const) ; 
 int ff_filter_get_nb_threads (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void averageiir2d(AVFilterContext *ctx, AVFrame *in, AVFrame *out, int plane)
{
    AverageBlurContext *s = ctx->priv;
    const int width = s->planewidth[plane];
    const int height = s->planeheight[plane];
    const int nb_threads = ff_filter_get_nb_threads(ctx);
    ThreadData td;

    td.width = width;
    td.height = height;
    td.ptr = in->data[plane];
    td.linesize = in->linesize[plane];
    ctx->internal->execute(ctx, s->filter_horizontally, &td, NULL, FFMIN(height, nb_threads));
    td.ptr = out->data[plane];
    td.linesize = out->linesize[plane];
    ctx->internal->execute(ctx, s->filter_vertically, &td, NULL, FFMIN(width, nb_threads));
}