#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ size; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {TYPE_2__* priv; scalar_t__ index; scalar_t__ type; TYPE_1__* component; } ;
struct TYPE_16__ {scalar_t__ (* pf_parameter_set ) (TYPE_3__*,TYPE_4__ const*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_PARAMETER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_PORT (TYPE_3__*) ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int,int,TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  UNLOCK_PORT (TYPE_3__*) ; 
 scalar_t__ mmal_port_private_parameter_set (TYPE_3__*,TYPE_4__ const*) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__ const*) ; 

MMAL_STATUS_T mmal_port_parameter_set(MMAL_PORT_T *port,
   const MMAL_PARAMETER_HEADER_T *param)
{
   MMAL_STATUS_T status = MMAL_ENOSYS;

   if (!port)
   {
      LOG_ERROR("no port");
      return MMAL_EINVAL;
   }
   if (!param)
   {
      LOG_ERROR("param not supplied");
      return MMAL_EINVAL;
   }
   if (!port->priv)
   {
      LOG_ERROR("port not configured");
      return MMAL_EINVAL;
   }

   LOG_TRACE("%s(%i:%i) port %p, param %p (%x,%i)", port->component->name,
             (int)port->type, (int)port->index, port,
             param, param ? param->id : 0, param ? (int)param->size : 0);

   LOCK_PORT(port);
   if (port->priv->pf_parameter_set)
      status = port->priv->pf_parameter_set(port, param);
   if (status == MMAL_ENOSYS)
   {
      /* is this a core parameter? */
      status = mmal_port_private_parameter_set(port, param);
   }
   UNLOCK_PORT(port);
   return status;
}