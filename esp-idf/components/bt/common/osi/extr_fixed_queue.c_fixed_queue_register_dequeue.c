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
struct TYPE_3__ {int /*<<< orphan*/ * dequeue_ready; } ;
typedef  TYPE_1__ fixed_queue_t ;
typedef  int /*<<< orphan*/ * fixed_queue_cb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void fixed_queue_register_dequeue(fixed_queue_t *queue, fixed_queue_cb ready_cb)
{
    assert(queue != NULL);
    assert(ready_cb != NULL);

    queue->dequeue_ready = ready_cb;
}