#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* ilcs_common_deinit ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ilcs_thread_init ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ kill_service; int /*<<< orphan*/  thread; int /*<<< orphan*/  wait_mtx; int /*<<< orphan*/  send_sem; int /*<<< orphan*/  wait_event; TYPE_2__* wait; int /*<<< orphan*/  timer; int /*<<< orphan*/  queue; int /*<<< orphan*/  bulk_rx; int /*<<< orphan*/  service; int /*<<< orphan*/  ilcs_common; TYPE_1__ config; } ;
struct TYPE_7__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_3__ ILCS_SERVICE_T ;

/* Variables and functions */
 scalar_t__ CLOSED_CALLBACK ; 
 int ILCS_MAX_WAITING ; 
 int /*<<< orphan*/  ilcs_process_message (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_remove_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiu_queue_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_abort () ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_reap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_timer_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *ilcs_task(void *param)
{
   ILCS_SERVICE_T *st = (ILCS_SERVICE_T *) param;
   int i;

   st->config.ilcs_thread_init(st->ilcs_common);

   while(st->kill_service < CLOSED_CALLBACK)
      ilcs_process_message(st, 1);

   // tidy up after ourselves
   st->config.ilcs_common_deinit(st->ilcs_common);
#ifdef USE_VCHIQ_ARM
   vchiq_remove_service(st->service);
#endif
   vcos_event_delete(&st->bulk_rx);
   vchiu_queue_delete(&st->queue);
   vcos_timer_delete(&st->timer);
   for(i=0; i<ILCS_MAX_WAITING; i++)
      vcos_event_delete(&st->wait[i].event);
   vcos_event_delete(&st->wait_event);
   vcos_semaphore_delete(&st->send_sem);
   vcos_mutex_delete(&st->wait_mtx);

   if(st->kill_service == CLOSED_CALLBACK)
   {
#ifdef _VIDEOCORE
      // need vcos reaper thread to do join/free for us
      vcos_thread_reap(&st->thread, vcos_free, st);
#else
      // we've got a CLOSED callback from vchiq without ilcs_deinit being called.
      // this shouldn't really happen, so we just want to abort at this point.
      vcos_abort();
#endif
   }

   return 0;
}