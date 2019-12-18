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
struct TYPE_5__ {int created; int /*<<< orphan*/  sema; int /*<<< orphan*/  mutex; int /*<<< orphan*/  timer; int /*<<< orphan*/  wd_timer; scalar_t__ queue; scalar_t__ out_pool; scalar_t__ connection; int /*<<< orphan*/ * camera; int /*<<< orphan*/ * video_decode; int /*<<< orphan*/ * reader; } ;
typedef  TYPE_1__ SVP_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 int SVP_CREATED_MUTEX ; 
 int SVP_CREATED_SEM ; 
 int SVP_CREATED_TIMER ; 
 int SVP_CREATED_WD_TIMER ; 
 int /*<<< orphan*/  mmal_component_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_component_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_connection_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  svp_stop (TYPE_1__*) ; 
 int vcos_countof (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_timer_delete (int /*<<< orphan*/ *) ; 

void svp_destroy(SVP_T *svp)
{
   if (svp)
   {
      MMAL_COMPONENT_T *components[] = { svp->reader, svp->video_decode, svp->camera };
      MMAL_COMPONENT_T **comp;

      /* Stop thread, disable connection and components */
      svp_stop(svp);

      for (comp = components; comp < components + vcos_countof(components); comp++)
      {
         mmal_component_disable(*comp);
      }

      /* Destroy connection + components */
      if (svp->connection)
      {
         mmal_connection_destroy(svp->connection);
      }

      for (comp = components; comp < components + vcos_countof(components); comp++)
      {
         mmal_component_destroy(*comp);
      }

      /* Free remaining resources */
      if (svp->out_pool)
      {
         mmal_pool_destroy(svp->out_pool);
      }

      if (svp->queue)
      {
         mmal_queue_destroy(svp->queue);
      }

      if (svp->created & SVP_CREATED_WD_TIMER)
      {
         vcos_timer_delete(&svp->wd_timer);
      }

      if (svp->created & SVP_CREATED_TIMER)
      {
         vcos_timer_delete(&svp->timer);
      }

      if (svp->created & SVP_CREATED_MUTEX)
      {
         vcos_mutex_delete(&svp->mutex);
      }

      if (svp->created & SVP_CREATED_SEM)
      {
         vcos_semaphore_delete(&svp->sema);
      }

      vcos_free(svp);
   }
}