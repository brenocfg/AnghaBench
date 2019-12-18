#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_14__ {scalar_t__ status; } ;
typedef  TYPE_4__ mmal_worker_reply ;
struct TYPE_11__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; } ;
struct TYPE_12__ {TYPE_1__ connect; } ;
struct TYPE_15__ {int /*<<< orphan*/  header; TYPE_2__ param; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  action; int /*<<< orphan*/  component_handle; } ;
typedef  TYPE_5__ mmal_worker_port_action ;
struct TYPE_17__ {TYPE_6__* connected; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; } ;
struct TYPE_16__ {TYPE_3__* priv; } ;
struct TYPE_13__ {scalar_t__ pf_enable; TYPE_7__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_ACTION ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_ACTION_CONNECT ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_ACTION_DISCONNECT ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_port_connect(MMAL_PORT_T *port, MMAL_PORT_T *other_port)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;
   MMAL_STATUS_T status;
   mmal_worker_reply reply;
   mmal_worker_port_action msg;
   size_t replylen = sizeof(reply);

   /* We only support connecting vc components together */
   if (other_port && port->priv->pf_enable != other_port->priv->pf_enable)
      return MMAL_ENOSYS;

   /* Send the request to the video side */
   msg.component_handle = module->component_handle;
   msg.action = other_port ? MMAL_WORKER_PORT_ACTION_CONNECT : MMAL_WORKER_PORT_ACTION_DISCONNECT;
   msg.port_handle = module->port_handle;
   if (other_port)
   {
      msg.param.connect.component_handle = other_port->priv->module->component_handle;
      msg.param.connect.port_handle = other_port->priv->module->port_handle;
   }

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg.header, sizeof(msg),
                                     MMAL_WORKER_PORT_ACTION, &reply, &replylen, MMAL_FALSE);
   if (status == MMAL_SUCCESS)
   {
      vcos_assert(replylen == sizeof(reply));
      status = reply.status;
   }

   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to connect ports: %s", mmal_status_to_string(status));
      return status;
   }

   if (other_port)
   {
      /* Connection */
      module->connected = other_port;
      other_port->priv->module->connected = port;
   }
   else
   {
      /* Disconnection */
      if (module->connected)
         module->connected->priv->module->connected = NULL;
      module->connected = NULL;
   }

   return MMAL_SUCCESS;
}