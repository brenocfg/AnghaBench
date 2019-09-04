#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fifo; scalar_t__ status_in; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 unsigned int FFMIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert1 (unsigned int) ; 
 int /*<<< orphan*/  consume_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_framequeue_queued_samples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_inlink_check_available_samples (TYPE_1__*,unsigned int) ; 
 int take_samples (TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ **) ; 

int ff_inlink_consume_samples(AVFilterLink *link, unsigned min, unsigned max,
                            AVFrame **rframe)
{
    AVFrame *frame;
    int ret;

    av_assert1(min);
    *rframe = NULL;
    if (!ff_inlink_check_available_samples(link, min))
        return 0;
    if (link->status_in)
        min = FFMIN(min, ff_framequeue_queued_samples(&link->fifo));
    ret = take_samples(link, min, max, &frame);
    if (ret < 0)
        return ret;
    consume_update(link, frame);
    *rframe = frame;
    return 1;
}