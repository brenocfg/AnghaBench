#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* container; } ;
struct TYPE_17__ {TYPE_3__* priv; } ;
struct TYPE_16__ {TYPE_5__* priv; TYPE_7__* component; } ;
struct TYPE_15__ {TYPE_4__* module; } ;
struct TYPE_14__ {unsigned int track; } ;
struct TYPE_13__ {TYPE_8__* module; } ;
struct TYPE_12__ {unsigned int tracks_num; TYPE_1__** tracks; } ;
struct TYPE_11__ {scalar_t__ is_enabled; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ container_port_flush (TYPE_6__*) ; 

__attribute__((used)) static MMAL_STATUS_T container_port_disable(MMAL_PORT_T *port)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   unsigned int track = port->priv->module->track;
   MMAL_STATUS_T status;

   if(!module->container || track >= module->container->tracks_num)
      return MMAL_EINVAL;

   /* Actions are prevented from running at that point so a flush
    * will return all buffers. */
   status = container_port_flush(port);
   if(status != MMAL_SUCCESS)
      return status;

   module->container->tracks[track]->is_enabled = 0;
   return MMAL_SUCCESS;
}