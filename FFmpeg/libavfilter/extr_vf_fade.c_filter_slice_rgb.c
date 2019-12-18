#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int height; } ;
struct TYPE_7__ {int bpp; scalar_t__ alpha; } ;
typedef  TYPE_1__ FadeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_rgb (TYPE_1__*,TYPE_2__*,int,int,int,int) ; 

__attribute__((used)) static int filter_slice_rgb(AVFilterContext *ctx, void *arg, int jobnr,
                            int nb_jobs)
{
    FadeContext *s = ctx->priv;
    AVFrame *frame = arg;
    int slice_start = (frame->height *  jobnr   ) / nb_jobs;
    int slice_end   = (frame->height * (jobnr+1)) / nb_jobs;

    if      (s->alpha)    filter_rgb(s, frame, slice_start, slice_end, 1, 4);
    else if (s->bpp == 3) filter_rgb(s, frame, slice_start, slice_end, 0, 3);
    else if (s->bpp == 4) filter_rgb(s, frame, slice_start, slice_end, 0, 4);
    else                  av_assert0(0);

    return 0;
}