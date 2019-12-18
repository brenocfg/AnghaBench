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
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {unsigned int input_num; unsigned int output_num; scalar_t__ is_enabled; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; TYPE_1__* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ (* pf_disable ) (TYPE_2__*) ;} ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_CORE_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 scalar_t__ mmal_port_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_component_disable(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_CORE_PRIVATE_T *private;
   MMAL_STATUS_T status = MMAL_ENOSYS;
   unsigned int i;

   if (!component)
      return MMAL_EINVAL;

   private = (MMAL_COMPONENT_CORE_PRIVATE_T *)component->priv;

   LOG_TRACE("%s %d", component->name, component->id);

   vcos_mutex_lock(&private->lock);

   /* Check we have anything to do */
   if (!component->is_enabled)
   {
      vcos_mutex_unlock(&private->lock);
      return MMAL_SUCCESS;
   }

   if (component->priv->pf_disable)
      status = component->priv->pf_disable(component);

   /* If the component does not support enable/disable, we handle that
    * in the core itself */
   if (status == MMAL_ENOSYS)
   {
      status = MMAL_SUCCESS;

      /* Pause all input / output ports */
      for (i = 0; status == MMAL_SUCCESS && i < component->input_num; i++)
         status = mmal_port_pause(component->input[i], MMAL_TRUE);
      for (i = 0; status == MMAL_SUCCESS && i < component->output_num; i++)
         status = mmal_port_pause(component->output[i], MMAL_TRUE);
   }

   if (status == MMAL_SUCCESS)
      component->is_enabled = 0;

   vcos_mutex_unlock(&private->lock);

   return status;
}