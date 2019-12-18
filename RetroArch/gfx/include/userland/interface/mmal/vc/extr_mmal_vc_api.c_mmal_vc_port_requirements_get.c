#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_11__ {int /*<<< orphan*/  header; int /*<<< orphan*/  index; int /*<<< orphan*/  port_type; int /*<<< orphan*/  component_handle; } ;
typedef  TYPE_3__ mmal_worker_port_info_get ;
struct TYPE_10__ {int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; } ;
struct TYPE_12__ {scalar_t__ status; TYPE_2__ port; } ;
typedef  TYPE_4__ mmal_worker_port_info ;
struct TYPE_14__ {int /*<<< orphan*/  component_handle; } ;
struct TYPE_13__ {int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  index; int /*<<< orphan*/  type; TYPE_1__* priv; } ;
struct TYPE_9__ {TYPE_6__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_INFO_GET ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_port_requirements_get(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;
   mmal_worker_port_info_get msg;
   mmal_worker_port_info reply;
   size_t replylen = sizeof(reply);
   MMAL_STATUS_T status;

   msg.component_handle = module->component_handle;
   msg.port_type = port->type;
   msg.index = port->index;

   LOG_TRACE("get port requirements (%i:%i)", port->type, port->index);

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg.header, sizeof(msg),
                                     MMAL_WORKER_PORT_INFO_GET, &reply, &replylen, MMAL_FALSE);
   if (status == MMAL_SUCCESS)
   {
      vcos_assert(replylen == sizeof(reply));
      status = reply.status;
   }
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to get port requirements (%i:%i)", port->type, port->index);
      return status;
   }

   port->buffer_num_min = reply.port.buffer_num_min;
   port->buffer_num_recommended = reply.port.buffer_num_recommended;
   port->buffer_size_min = reply.port.buffer_size_min;
   port->buffer_size_recommended = reply.port.buffer_size_recommended;
   port->buffer_alignment_min = reply.port.buffer_alignment_min;

   return MMAL_SUCCESS;
}