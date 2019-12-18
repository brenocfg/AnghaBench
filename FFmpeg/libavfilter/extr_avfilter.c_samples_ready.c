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
struct TYPE_3__ {scalar_t__ status_in; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ ff_framequeue_queued_frames (int /*<<< orphan*/ *) ; 
 unsigned int ff_framequeue_queued_samples (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samples_ready(AVFilterLink *link, unsigned min)
{
    return ff_framequeue_queued_frames(&link->fifo) &&
           (ff_framequeue_queued_samples(&link->fifo) >= min ||
            link->status_in);
}