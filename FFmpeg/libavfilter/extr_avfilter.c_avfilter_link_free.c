#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame_pool; int /*<<< orphan*/  fifo; int /*<<< orphan*/  partial_buf; } ;
typedef  int /*<<< orphan*/  FFFramePool ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_frame_pool_uninit (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_framequeue_free (int /*<<< orphan*/ *) ; 

void avfilter_link_free(AVFilterLink **link)
{
    if (!*link)
        return;

    av_frame_free(&(*link)->partial_buf);
    ff_framequeue_free(&(*link)->fifo);
    ff_frame_pool_uninit((FFFramePool**)&(*link)->frame_pool);

    av_freep(link);
}