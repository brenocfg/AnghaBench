#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int nb_inputs; int nb_planes; TYPE_1__* items; TYPE_3__** frames; } ;
struct TYPE_6__ {int* y; int /*<<< orphan*/ * height; int /*<<< orphan*/ * linesize; scalar_t__* x; } ;
typedef  TYPE_1__ StackItem ;
typedef  TYPE_2__ StackContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_slice(AVFilterContext *ctx, void *arg, int job, int nb_jobs)
{
    StackContext *s = ctx->priv;
    AVFrame *out = arg;
    AVFrame **in = s->frames;
    const int start = (s->nb_inputs *  job   ) / nb_jobs;
    const int end   = (s->nb_inputs * (job+1)) / nb_jobs;

    for (int i = start; i < end; i++) {
        StackItem *item = &s->items[i];

        for (int p = 0; p < s->nb_planes; p++) {
            av_image_copy_plane(out->data[p] + out->linesize[p] * item->y[p] + item->x[p],
                                out->linesize[p],
                                in[i]->data[p],
                                in[i]->linesize[p],
                                item->linesize[p], item->height[p]);
        }
    }

    return 0;
}