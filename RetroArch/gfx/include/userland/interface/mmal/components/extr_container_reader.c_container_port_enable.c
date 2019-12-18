#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {size_t tracks_num; TYPE_4__** tracks; } ;
struct TYPE_18__ {TYPE_9__* container; scalar_t__ writer; } ;
struct TYPE_17__ {TYPE_1__* priv; } ;
struct TYPE_16__ {size_t track; int /*<<< orphan*/  format; } ;
struct TYPE_15__ {TYPE_3__* format; TYPE_2__* priv; TYPE_7__* component; } ;
struct TYPE_14__ {int is_enabled; } ;
struct TYPE_13__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_12__ {TYPE_6__* module; } ;
struct TYPE_11__ {TYPE_8__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_PORT_MODULE_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_BH_CB_T ;
typedef  TYPE_7__ MMAL_COMPONENT_T ;
typedef  TYPE_8__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,char*,size_t,...) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_TRACK_ADD ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  container_map_to_mmal_status (scalar_t__) ; 
 scalar_t__ vc_container_control (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T container_port_enable(MMAL_PORT_T *port, MMAL_PORT_BH_CB_T cb)
{
   MMAL_COMPONENT_T *component = port->component;
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   MMAL_PORT_MODULE_T *port_module = port->priv->module;
   MMAL_PARAM_UNUSED(cb);

   if(!module->container)
      return MMAL_EINVAL;

   if(module->writer)
   {
      VC_CONTAINER_STATUS_T cstatus;
      port_module->track = module->container->tracks_num;
      cstatus = vc_container_control(module->container, VC_CONTAINER_CONTROL_TRACK_ADD,
                                     port_module->format);
      if(cstatus != VC_CONTAINER_SUCCESS)
      {
         LOG_ERROR("error adding track %4.4s (%i)", (char *)&port->format->encoding, (int)cstatus);
         return container_map_to_mmal_status(cstatus);
      }
   }

   if(port_module->track >= module->container->tracks_num)
      {
      LOG_ERROR("error 1 adding track %4.4s (%i/%i)", (char *)&port->format->encoding, port_module->track, module->container->tracks_num);
      return MMAL_EINVAL;
      }
   module->container->tracks[port_module->track]->is_enabled = 1;
   return MMAL_SUCCESS;
}