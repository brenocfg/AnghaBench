#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* internal; int /*<<< orphan*/ * av_class; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_queues; } ;
typedef  TYPE_2__ AVFilterGraph ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_framequeue_global_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filtergraph_class ; 

AVFilterGraph *avfilter_graph_alloc(void)
{
    AVFilterGraph *ret = av_mallocz(sizeof(*ret));
    if (!ret)
        return NULL;

    ret->internal = av_mallocz(sizeof(*ret->internal));
    if (!ret->internal) {
        av_freep(&ret);
        return NULL;
    }

    ret->av_class = &filtergraph_class;
    av_opt_set_defaults(ret);
    ff_framequeue_global_init(&ret->internal->frame_queues);

    return ret;
}