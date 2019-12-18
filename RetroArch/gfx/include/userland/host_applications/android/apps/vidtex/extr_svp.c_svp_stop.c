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
struct TYPE_4__ {int created; int /*<<< orphan*/  video_output; scalar_t__ connection; int /*<<< orphan*/  thread; int /*<<< orphan*/  sema; int /*<<< orphan*/  timer; int /*<<< orphan*/  wd_timer; } ;
typedef  TYPE_1__ SVP_T ;

/* Variables and functions */
 int SVP_CREATED_THREAD ; 
 int /*<<< orphan*/  SVP_STOP_USER ; 
 int /*<<< orphan*/  mmal_connection_disable (scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svp_set_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_timer_cancel (int /*<<< orphan*/ *) ; 

void svp_stop(SVP_T *svp)
{
   vcos_timer_cancel(&svp->wd_timer);
   vcos_timer_cancel(&svp->timer);

   /* Stop worker thread */
   if (svp->created & SVP_CREATED_THREAD)
   {
      svp_set_stop(svp, SVP_STOP_USER);
      vcos_semaphore_post(&svp->sema);
      vcos_thread_join(&svp->thread, NULL);
      svp->created &= ~SVP_CREATED_THREAD;
   }

   if (svp->connection)
   {
      mmal_connection_disable(svp->connection);
   }

   mmal_port_disable(svp->video_output);
}