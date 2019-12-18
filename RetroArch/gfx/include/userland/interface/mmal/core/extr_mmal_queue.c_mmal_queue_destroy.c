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
struct TYPE_4__ {int /*<<< orphan*/  semaphore; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ MMAL_QUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

void mmal_queue_destroy(MMAL_QUEUE_T *queue)
{
   if(!queue) return;
   vcos_mutex_delete(&queue->lock);
   vcos_semaphore_delete(&queue->semaphore);
   vcos_free(queue);
}