#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {struct TYPE_9__* port; scalar_t__ control; TYPE_1__* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {scalar_t__ (* pf_destroy ) (TYPE_2__*) ;scalar_t__ event_pool; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_CORE_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_action_deregister (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_core_deinit () ; 
 int /*<<< orphan*/  mmal_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_port_free (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_destroy_internal(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_CORE_PRIVATE_T *private = (MMAL_COMPONENT_CORE_PRIVATE_T *)component->priv;
   MMAL_STATUS_T status;

   LOG_TRACE("%s %d", component->name, component->id);

   mmal_component_action_deregister(component);

   /* Should pf_destroy be allowed to fail ?
    * If so, what do we do if it fails ?
    */
   if (component->priv->pf_destroy)
   {
      status = component->priv->pf_destroy(component);
      if(!vcos_verify(status == MMAL_SUCCESS))
         return status;
   }

   if (component->priv->event_pool)
      mmal_pool_destroy(component->priv->event_pool);

   if (component->control)
      mmal_port_free(component->control);

   if (component->port)
      vcos_free(component->port);

   vcos_mutex_delete(&private->lock);
   vcos_free(component);
   mmal_core_deinit();
   return MMAL_SUCCESS;
}