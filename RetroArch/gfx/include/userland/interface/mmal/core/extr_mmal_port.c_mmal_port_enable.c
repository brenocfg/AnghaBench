#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ core_owns_connection; TYPE_2__* connected_port; } ;
struct TYPE_27__ {scalar_t__ type; scalar_t__ is_enabled; struct TYPE_27__* name; TYPE_1__* priv; scalar_t__ buffer_size_min; scalar_t__ buffer_size_recommended; scalar_t__ buffer_size; scalar_t__ buffer_num_min; scalar_t__ buffer_num_recommended; scalar_t__ buffer_num; } ;
struct TYPE_26__ {TYPE_3__* core; int /*<<< orphan*/  pf_enable; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PORT_PRIVATE_CORE_T ;
typedef  TYPE_2__* MMAL_PORT_BH_CB_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_CONNECTION (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,TYPE_2__*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int,int,int,int,int,int) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_PORT_TYPE_INPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK_CONNECTION (TYPE_2__*) ; 
 TYPE_2__* mmal_port_connected_input_cb ; 
 TYPE_2__* mmal_port_connected_output_cb ; 
 int /*<<< orphan*/  mmal_port_connection_disable (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ mmal_port_connection_enable (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ mmal_port_connection_start (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_disable_internal (TYPE_2__*) ; 
 scalar_t__ mmal_port_enable_internal (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* mmal_status_to_string (scalar_t__) ; 

MMAL_STATUS_T mmal_port_enable(MMAL_PORT_T *port, MMAL_PORT_BH_CB_T cb)
{
   MMAL_STATUS_T status;
   MMAL_PORT_T *connected_port;
   MMAL_PORT_PRIVATE_CORE_T *core;

   if (!port || !port->priv)
      return MMAL_EINVAL;

   LOG_TRACE("%s port %p, cb %p, buffers (%i/%i/%i,%i/%i/%i)",
             port->name, port, cb,
             (int)port->buffer_num, (int)port->buffer_num_recommended, (int)port->buffer_num_min,
             (int)port->buffer_size, (int)port->buffer_size_recommended, (int)port->buffer_size_min);

   if (!port->priv->pf_enable)
      return MMAL_ENOSYS;

   core = port->priv->core;
   LOCK_CONNECTION(port);
   connected_port = core->connected_port;

   /* Sanity checking */
   if (port->is_enabled)
   {
      UNLOCK_CONNECTION(port);
      LOG_ERROR("%s(%p) already enabled", port->name, port);
      return MMAL_EINVAL;
   }
   if (connected_port && cb) /* Callback must be NULL for connected ports */
   {
      UNLOCK_CONNECTION(port);
      LOG_ERROR("callback (%p) not allowed for connected port (%s)%p",
         cb, port->name, connected_port);
      return MMAL_EINVAL;
   }

   /* Start by preparing the port connection so that everything is ready for when
    * both ports are enabled */
   if (connected_port)
   {
      LOCK_CONNECTION(connected_port);
      status = mmal_port_connection_enable(port, connected_port);
      if (status != MMAL_SUCCESS)
      {
         UNLOCK_CONNECTION(connected_port);
         UNLOCK_CONNECTION(port);
         return status;
      }

      cb = connected_port->type == MMAL_PORT_TYPE_INPUT ?
         mmal_port_connected_output_cb : mmal_port_connected_input_cb;
   }

   /* Enable the input port of a connection first */
   if (connected_port && connected_port->type == MMAL_PORT_TYPE_INPUT)
   {
      status = mmal_port_enable_internal(connected_port, mmal_port_connected_input_cb);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("failed to enable connected port (%s)%p (%s)", connected_port->name,
            connected_port, mmal_status_to_string(status));
         goto error;
      }
   }

   status = mmal_port_enable_internal(port, cb);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to enable port %s(%p) (%s)", port->name, port,
         mmal_status_to_string(status));
      goto error;
   }

   /* Enable the output port of a connection last */
   if (connected_port && connected_port->type != MMAL_PORT_TYPE_INPUT)
   {
      status = mmal_port_enable_internal(connected_port, mmal_port_connected_output_cb);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("failed to enable connected port (%s)%p (%s)", connected_port->name,
            connected_port, mmal_status_to_string(status));
         goto error;
      }
   }

   /* Kick off the connection */
   if (connected_port && core->core_owns_connection)
   {
      status = mmal_port_connection_start(port, connected_port);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("failed to start connection (%s)%p (%s)", port->name,
            port, mmal_status_to_string(status));
         goto error;
      }
   }

   if (connected_port)
      UNLOCK_CONNECTION(connected_port);
   UNLOCK_CONNECTION(port);
   return MMAL_SUCCESS;

error:
   if (connected_port && connected_port->is_enabled)
      mmal_port_disable_internal(connected_port);
   if (port->is_enabled)
      mmal_port_disable_internal(port);
   if (connected_port)
      mmal_port_connection_disable(port, connected_port);

   if (connected_port)
      UNLOCK_CONNECTION(connected_port);
   UNLOCK_CONNECTION(port);
   return status;
}