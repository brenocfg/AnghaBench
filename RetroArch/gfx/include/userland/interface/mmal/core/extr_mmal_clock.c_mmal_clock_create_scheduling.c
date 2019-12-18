#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int VCOS_UNSIGNED ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_8__ {void* list_pending; void* list_free; TYPE_1__* pool; } ;
struct TYPE_9__ {TYPE_2__ request; int /*<<< orphan*/  timer; int /*<<< orphan*/  event; int /*<<< orphan*/  scheduling; int /*<<< orphan*/  thread; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_CLOCK_PRIVATE_T ;
typedef  scalar_t__ MMAL_BOOL_T ;

/* Variables and functions */
 unsigned int CLOCK_REQUEST_SLOTS ; 
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 scalar_t__ MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int VCOS_AFFINITY_MASK ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 scalar_t__ mmal_clock_timer_create (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_clock_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_worker_thread ; 
 void* mmal_list_create () ; 
 int /*<<< orphan*/  mmal_list_destroy (void*) ; 
 int /*<<< orphan*/  mmal_list_push_back (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int vcos_thread_get_priority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_set_priority (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_clock_create_scheduling(MMAL_CLOCK_PRIVATE_T *private)
{
   unsigned int i;
   MMAL_BOOL_T timer_status = MMAL_FALSE;
   VCOS_STATUS_T event_status = VCOS_EINVAL;
   VCOS_UNSIGNED priority;

   timer_status = mmal_clock_timer_create(&private->timer, private);
   if (!timer_status)
   {
      LOG_ERROR("failed to create timer %p", private);
      goto error;
   }

   event_status = vcos_semaphore_create(&private->event, "mmal-clock sema", 0);
   if (event_status != VCOS_SUCCESS)
   {
      LOG_ERROR("failed to create event semaphore %d", event_status);
      goto error;
   }

   private->request.list_free = mmal_list_create();
   private->request.list_pending = mmal_list_create();
   if (!private->request.list_free || !private->request.list_pending)
   {
      LOG_ERROR("failed to create list %p %p", private->request.list_free, private->request.list_pending);
      goto error;
   }

   /* Populate the list of available request slots */
   for (i = 0; i < CLOCK_REQUEST_SLOTS; ++i)
      mmal_list_push_back(private->request.list_free, &private->request.pool[i].link);

   if (vcos_thread_create(&private->thread, "mmal-clock thread", NULL,
                          mmal_clock_worker_thread, private) != VCOS_SUCCESS)
   {
      LOG_ERROR("failed to create worker thread");
      goto error;
   }
   priority = vcos_thread_get_priority(&private->thread);
   vcos_thread_set_priority(&private->thread, 1 | (priority & VCOS_AFFINITY_MASK));

   private->scheduling = MMAL_TRUE;

   return MMAL_SUCCESS;

error:
   if (event_status == VCOS_SUCCESS) vcos_semaphore_delete(&private->event);
   if (timer_status) mmal_clock_timer_destroy(&private->timer);
   if (private->request.list_free) mmal_list_destroy(private->request.list_free);
   if (private->request.list_pending) mmal_list_destroy(private->request.list_pending);
   return MMAL_ENOSPC;
}