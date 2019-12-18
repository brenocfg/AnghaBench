#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_1__ MMAL_QUEUE_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/ * mmal_queue_get_core (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 
 scalar_t__ vcos_semaphore_trywait (int /*<<< orphan*/ *) ; 

MMAL_BUFFER_HEADER_T *mmal_queue_get(MMAL_QUEUE_T *queue)
{
   vcos_assert(queue);
   if(!queue) return 0;

   if(vcos_semaphore_trywait(&queue->semaphore) != VCOS_SUCCESS)
       return NULL;

   return mmal_queue_get_core(queue);
}