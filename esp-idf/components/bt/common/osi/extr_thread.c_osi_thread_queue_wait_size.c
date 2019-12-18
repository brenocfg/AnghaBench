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
struct TYPE_3__ {int work_queue_num; int /*<<< orphan*/ * work_queues; } ;
typedef  TYPE_1__ osi_thread_t ;

/* Variables and functions */
 int fixed_queue_length (int /*<<< orphan*/ ) ; 

int osi_thread_queue_wait_size(osi_thread_t *thread, int wq_idx)
{
    if (wq_idx < 0 || wq_idx >= thread->work_queue_num) {
        return -1;
    }

    return fixed_queue_length(thread->work_queues[wq_idx]);
}