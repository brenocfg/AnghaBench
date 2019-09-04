#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct TYPE_3__ {scalar_t__ status_in; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (unsigned int) ; 
 unsigned int ff_framequeue_queued_samples (int /*<<< orphan*/ *) ; 

int ff_inlink_check_available_samples(AVFilterLink *link, unsigned min)
{
    uint64_t samples = ff_framequeue_queued_samples(&link->fifo);
    av_assert1(min);
    return samples >= min || (link->status_in && samples);
}