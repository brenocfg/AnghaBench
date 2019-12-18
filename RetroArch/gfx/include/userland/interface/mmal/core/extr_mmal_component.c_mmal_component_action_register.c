#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_THREAD_ATTR_T ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_8__ {int /*<<< orphan*/  priority; } ;
struct TYPE_10__ {void (* pf_action ) (TYPE_2__*) ;int /*<<< orphan*/  action_event; int /*<<< orphan*/  action_mutex; int /*<<< orphan*/  action_thread; TYPE_1__ private; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; scalar_t__ priv; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_CORE_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_action_thread_func ; 
 scalar_t__ vcos_event_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_attr_setpriority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

MMAL_STATUS_T mmal_component_action_register(MMAL_COMPONENT_T *component,
                                             void (*pf_action)(MMAL_COMPONENT_T *) )
{
   MMAL_COMPONENT_CORE_PRIVATE_T *private = (MMAL_COMPONENT_CORE_PRIVATE_T *)component->priv;
   VCOS_THREAD_ATTR_T attrs;
   VCOS_STATUS_T status;

   if (private->pf_action)
      return MMAL_EINVAL;

   status = vcos_event_create(&private->action_event, component->name);
   if (status != VCOS_SUCCESS)
      return MMAL_ENOMEM;

   status = vcos_mutex_create(&private->action_mutex, component->name);
   if (status != VCOS_SUCCESS)
   {
      vcos_event_delete(&private->action_event);
      return MMAL_ENOMEM;
   }

   vcos_thread_attr_init(&attrs);
   vcos_thread_attr_setpriority(&attrs,
                                private->private.priority);
   status = vcos_thread_create(&private->action_thread, component->name, &attrs,
                               mmal_component_action_thread_func, component);
   if (status != VCOS_SUCCESS)
   {
      vcos_mutex_delete(&private->action_mutex);
      vcos_event_delete(&private->action_event);
      return MMAL_ENOMEM;
   }

   private->pf_action = pf_action;
   return MMAL_SUCCESS;
}