#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reply ;
struct TYPE_12__ {scalar_t__ status; } ;
typedef  TYPE_3__ mmal_worker_reply ;
struct TYPE_11__ {void* magic; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; TYPE_5__* client_context; } ;
struct TYPE_13__ {int /*<<< orphan*/  header; TYPE_2__ drvbuf; } ;
typedef  TYPE_4__ mmal_worker_buffer_from_host ;
struct TYPE_16__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; } ;
struct TYPE_15__ {TYPE_1__* priv; } ;
struct TYPE_14__ {TYPE_6__* port; void* magic; TYPE_4__ msg; } ;
struct TYPE_10__ {TYPE_7__* module; } ;
typedef  TYPE_5__ MMAL_VC_CLIENT_BUFFER_CONTEXT_T ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__) ; 
 void* MMAL_MAGIC ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_FLUSH ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_port_flush_sync(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;
   MMAL_STATUS_T status;
   mmal_worker_reply reply;
   MMAL_VC_CLIENT_BUFFER_CONTEXT_T client_context;
   mmal_worker_buffer_from_host *msg;

   size_t replylen = sizeof(reply);

   msg = &client_context.msg;

   client_context.magic = MMAL_MAGIC;
   client_context.port = port;

   msg->drvbuf.client_context = &client_context;
   msg->drvbuf.component_handle = module->component_handle;
   msg->drvbuf.port_handle = module->port_handle;
   msg->drvbuf.magic = MMAL_MAGIC;

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg->header, sizeof(*msg),
                                     MMAL_WORKER_PORT_FLUSH, &reply, &replylen, MMAL_TRUE);
   if (status == MMAL_SUCCESS)
   {
      vcos_assert(replylen == sizeof(reply));
      status = reply.status;
   }
   if (status != MMAL_SUCCESS)
      LOG_ERROR("failed to disable port - reason %d", status);

   return status;
}