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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ fixed_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int list_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 

bool fixed_queue_is_empty(fixed_queue_t *queue)
{
    bool is_empty = false;

    if (queue == NULL) {
        return true;
    }

    osi_mutex_lock(&queue->lock, OSI_MUTEX_MAX_TIMEOUT);
    is_empty = list_is_empty(queue->list);
    osi_mutex_unlock(&queue->lock);

    return is_empty;
}