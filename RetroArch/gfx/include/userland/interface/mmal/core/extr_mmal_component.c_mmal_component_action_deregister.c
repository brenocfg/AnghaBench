#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int action_quit; int /*<<< orphan*/ * pf_action; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  action_event; int /*<<< orphan*/  action_thread; } ;
struct TYPE_4__ {scalar_t__ priv; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;
typedef  TYPE_2__ MMAL_COMPONENT_CORE_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_component_action_deregister(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_CORE_PRIVATE_T *private = (MMAL_COMPONENT_CORE_PRIVATE_T *)component->priv;

   if (!private->pf_action)
      return MMAL_EINVAL;

   private->action_quit = 1;
   vcos_event_signal(&private->action_event);
   vcos_thread_join(&private->action_thread, NULL);
   vcos_event_delete(&private->action_event);
   vcos_mutex_delete(&private->action_mutex);
   private->pf_action = NULL;
   private->action_quit = 0;
   return MMAL_SUCCESS;
}