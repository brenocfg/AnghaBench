#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_12__ {int /*<<< orphan*/  header; int /*<<< orphan*/  index; int /*<<< orphan*/  port_type; int /*<<< orphan*/  component_handle; } ;
typedef  TYPE_3__ mmal_worker_port_info_get ;
struct TYPE_16__ {int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/ * es; } ;
struct TYPE_11__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; } ;
struct TYPE_13__ {scalar_t__ status; int /*<<< orphan*/  extradata; int /*<<< orphan*/  es; TYPE_9__ format; TYPE_2__ port; int /*<<< orphan*/  port_handle; } ;
typedef  TYPE_4__ mmal_worker_port_info ;
struct TYPE_15__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; } ;
struct TYPE_14__ {TYPE_9__* format; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  buffer_alignment_min; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_num; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  index; int /*<<< orphan*/  type; TYPE_1__* priv; } ;
struct TYPE_10__ {TYPE_6__* module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_INFO_GET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_format_extradata_alloc (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_port_info_get(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;
   mmal_worker_port_info_get msg;
   mmal_worker_port_info reply;
   size_t replylen = sizeof(reply);
   MMAL_STATUS_T status;

   msg.component_handle = module->component_handle;
   msg.port_type = port->type;
   msg.index = port->index;

   LOG_TRACE("get port info (%i:%i)", port->type, port->index);

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg.header, sizeof(msg),
                                     MMAL_WORKER_PORT_INFO_GET, &reply, &replylen, MMAL_FALSE);
   if (status == MMAL_SUCCESS)
   {
      vcos_assert(replylen == sizeof(reply));
      status = reply.status;
   }

   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to get port info (%i:%i): %s", port->type, port->index,
                mmal_status_to_string(status));
      return status;
   }

   module->port_handle = reply.port_handle;
   port->buffer_num_min = reply.port.buffer_num_min;
   port->buffer_num_recommended = reply.port.buffer_num_recommended;
   port->buffer_num = reply.port.buffer_num;
   port->buffer_size_min = reply.port.buffer_size_min;
   port->buffer_size_recommended = reply.port.buffer_size_recommended;
   port->buffer_size = reply.port.buffer_size;
   port->buffer_alignment_min = reply.port.buffer_alignment_min;
   port->is_enabled = reply.port.is_enabled;
   port->capabilities = reply.port.capabilities;
   reply.format.extradata = port->format->extradata;
   reply.format.es = port->format->es;
   *port->format = reply.format;
   *port->format->es = reply.es;
   if(port->format->extradata_size)
   {
      status = mmal_format_extradata_alloc(port->format, port->format->extradata_size);
      if(status != MMAL_SUCCESS)
      {
         vcos_assert(0);
         port->format->extradata_size = 0;
         LOG_ERROR("couldn't allocate extradata %i", port->format->extradata_size);
         return MMAL_ENOMEM;
      }
      memcpy(port->format->extradata, reply.extradata, port->format->extradata_size);
   }

   return MMAL_SUCCESS;
}