#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* priv; } ;
struct TYPE_13__ {scalar_t__ container; } ;
struct TYPE_12__ {unsigned int input_num; unsigned int output_num; TYPE_7__** output; TYPE_7__** input; TYPE_1__* priv; } ;
struct TYPE_11__ {TYPE_2__* module; } ;
struct TYPE_10__ {scalar_t__ queue; scalar_t__ format; } ;
struct TYPE_9__ {TYPE_5__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_ports_free (TYPE_7__**,int) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_close (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_format_delete (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_5__*) ; 

__attribute__((used)) static MMAL_STATUS_T container_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   unsigned int i;

   if(module->container)
      vc_container_close(module->container);

   for(i = 0; i < component->input_num; i++)
   {
      if(component->input[i]->priv->module->queue)
         mmal_queue_destroy(component->input[i]->priv->module->queue);
      if(component->input[i]->priv->module->format)
         vc_container_format_delete(component->input[i]->priv->module->format);
   }
   if(component->input_num)
      mmal_ports_free(component->input, component->input_num);

   for(i = 0; i < component->output_num; i++)
      if(component->output[i]->priv->module->queue)
         mmal_queue_destroy(component->output[i]->priv->module->queue);
   if(component->output_num)
      mmal_ports_free(component->output, component->output_num);

   vcos_free(module);
   return MMAL_SUCCESS;
}