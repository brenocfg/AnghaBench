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
struct TYPE_6__ {int /*<<< orphan*/  lock; scalar_t__ first; scalar_t__* last; scalar_t__ length; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_1__ MMAL_QUEUE_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  mmal_queue_sanity_check (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 TYPE_1__* vcos_malloc (int,char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

MMAL_QUEUE_T *mmal_queue_create(void)
{
   MMAL_QUEUE_T *queue;

   queue = vcos_malloc(sizeof(*queue), "MMAL queue");
   if(!queue) return 0;

   if(vcos_mutex_create(&queue->lock, "MMAL queue lock") != VCOS_SUCCESS )
   {
      vcos_free(queue);
      return 0;
   }

   if(vcos_semaphore_create(&queue->semaphore, "MMAL queue sema", 0) != VCOS_SUCCESS )
   {
      vcos_mutex_delete(&queue->lock);
      vcos_free(queue);
      return 0;
   }

   /* gratuitous lock for coverity */ vcos_mutex_lock(&queue->lock);
   queue->length = 0;
   queue->first = 0;
   queue->last = &queue->first;
   mmal_queue_sanity_check(queue, NULL);
   /* gratuitous unlock for coverity */ vcos_mutex_unlock(&queue->lock);

   return queue;
}