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
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_3__ {int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ fixed_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

list_t *fixed_queue_get_list(fixed_queue_t *queue)
{
    assert(queue != NULL);

    // NOTE: This function is not thread safe, and there is no point for
    // calling osi_mutex_lock() / osi_mutex_unlock()
    return queue->list;
}