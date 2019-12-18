#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_15__ {scalar_t__ status; } ;
typedef  TYPE_4__ mmal_worker_reply ;
struct TYPE_16__ {int /*<<< orphan*/  header; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  action; int /*<<< orphan*/  component_handle; } ;
typedef  TYPE_5__ mmal_worker_port_action ;
struct TYPE_18__ {scalar_t__ connected; scalar_t__ has_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  port_handle; int /*<<< orphan*/  component_handle; } ;
struct TYPE_17__ {scalar_t__ buffer_num; TYPE_10__* component; TYPE_1__* priv; } ;
struct TYPE_14__ {TYPE_2__* module; } ;
struct TYPE_13__ {int /*<<< orphan*/  callback_queue; } ;
struct TYPE_12__ {TYPE_7__* module; } ;
struct TYPE_11__ {TYPE_3__* priv; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  TYPE_7__ MMAL_PORT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_ACTION ; 
 int /*<<< orphan*/  MMAL_WORKER_PORT_ACTION_DISABLE ; 
 scalar_t__ mmal_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_vc_do_callback (TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 int /*<<< orphan*/  mmal_vc_port_info_get (scalar_t__) ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_blockpool_available_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_blockpool_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_port_disable(MMAL_PORT_T *port)
{
   MMAL_PORT_MODULE_T *module = port->priv->module;
   MMAL_STATUS_T status;
   mmal_worker_reply reply;
   mmal_worker_port_action msg;
   size_t replylen = sizeof(reply);

   msg.component_handle = module->component_handle;
   msg.action = MMAL_WORKER_PORT_ACTION_DISABLE;
   msg.port_handle = module->port_handle;

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg.header, sizeof(msg),
                                     MMAL_WORKER_PORT_ACTION, &reply, &replylen, MMAL_FALSE);
   if (status == MMAL_SUCCESS)
   {
      vcos_assert(replylen == sizeof(reply));
      status = reply.status;
   }
   if (status != MMAL_SUCCESS)
      LOG_ERROR("failed to disable port - reason %d", status);

   if (module->has_pool)
   {
      /* MMAL server should make sure that all buffers are sent back before it
       * disables the port. */
      vcos_assert(vcos_blockpool_available_count(&module->pool) == port->buffer_num);
      vcos_blockpool_delete(&module->pool);
      module->has_pool = 0;
   }

   /* We need to make sure all the queued callbacks have been done */
   while (mmal_queue_length(port->component->priv->module->callback_queue))
      mmal_vc_do_callback(port->component);

   if (module->connected)
      mmal_vc_port_info_get(module->connected);

   return status;
}