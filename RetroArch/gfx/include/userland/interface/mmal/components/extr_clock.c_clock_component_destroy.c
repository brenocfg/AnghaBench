#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* priv; } ;
struct TYPE_13__ {scalar_t__ queue; scalar_t__ free; } ;
struct TYPE_15__ {TYPE_4__ events; } ;
struct TYPE_14__ {int clock_num; TYPE_8__** clock; TYPE_3__* priv; } ;
struct TYPE_12__ {TYPE_6__* module; } ;
struct TYPE_11__ {TYPE_1__* module; } ;
struct TYPE_10__ {TYPE_6__* stream; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_COMPONENT_T ;
typedef  TYPE_6__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_list_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_ports_clock_free (TYPE_8__**,unsigned int) ; 
 int /*<<< orphan*/  vcos_free (TYPE_6__*) ; 

__attribute__((used)) static MMAL_STATUS_T clock_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   unsigned int i;

   if (module->events.free)
      mmal_list_destroy(module->events.free);

   if (module->events.queue)
      mmal_list_destroy(module->events.queue);

   if (component->clock_num)
   {
      for (i = 0; i < component->clock_num; ++i)
         vcos_free(component->clock[i]->priv->module->stream);

      mmal_ports_clock_free(component->clock, component->clock_num);
   }

   vcos_free(module);

   return MMAL_SUCCESS;
}