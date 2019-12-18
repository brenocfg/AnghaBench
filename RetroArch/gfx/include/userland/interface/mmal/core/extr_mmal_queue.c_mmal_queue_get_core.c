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
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  length; TYPE_2__* first; TYPE_2__** last; } ;
typedef  TYPE_1__ MMAL_QUEUE_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_queue_sanity_check (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_BUFFER_HEADER_T *mmal_queue_get_core(MMAL_QUEUE_T *queue)
{
   MMAL_BUFFER_HEADER_T * buffer;

   vcos_mutex_lock(&queue->lock);
   mmal_queue_sanity_check(queue, NULL);
   buffer = queue->first;
   vcos_assert(buffer != NULL);

   queue->first = buffer->next;
   if(!queue->first) queue->last = &queue->first;

   queue->length--;
   vcos_mutex_unlock(&queue->lock);

   return buffer;
}