#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ cmd; int /*<<< orphan*/  length; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  format; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; scalar_t__ is_enabled; int /*<<< orphan*/  component; int /*<<< orphan*/  format; TYPE_2__* priv; } ;
struct TYPE_17__ {TYPE_1__* core; } ;
struct TYPE_16__ {TYPE_3__* connected_port; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_event_error_send (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* mmal_event_format_changed_get (TYPE_5__*) ; 
 scalar_t__ mmal_format_full_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_format_commit (TYPE_3__*) ; 
 scalar_t__ mmal_port_send_buffer (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 

__attribute__((used)) static void mmal_port_connected_output_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_PORT_T* connected_port = port->priv->core->connected_port;
   MMAL_STATUS_T status;

   LOG_TRACE("buffer %p from connected output port %p: data %p, alloc_size %u, length %u",
             buffer, port, buffer->data, buffer->alloc_size, buffer->length);

   if (buffer->cmd)
   {
      MMAL_EVENT_FORMAT_CHANGED_T *event = mmal_event_format_changed_get(buffer);

      /* Handle format changed events */
      if (event)
      {
         /* Apply the change */
         status = mmal_format_full_copy(port->format, event->format);
         if (status == MMAL_SUCCESS)
            status = mmal_port_format_commit(port);
         if (status != MMAL_SUCCESS)
            LOG_ERROR("format commit failed on port %s (%i)", port->name, status);

         /* Forward to the connected port */
         if (status == MMAL_SUCCESS)
            status = mmal_port_send_buffer(connected_port, buffer);

         if (status != MMAL_SUCCESS)
         {
            mmal_event_error_send(port->component, status);
            mmal_buffer_header_release(buffer);
         }
         return; /* Event handled */
      }

      /* FIXME Release other event buffers for now, until we can deal with shared memory issues */
      mmal_buffer_header_release(buffer);
   }
   else
   {
      if (port->is_enabled)
      {
         /* Forward data buffers to the connected input port */
         status = mmal_port_send_buffer(connected_port, buffer);
         if (status != MMAL_SUCCESS)
         {
            LOG_ERROR("%s could not send buffer on port %s (%s)",
                      port->name, connected_port->name, mmal_status_to_string(status));
            mmal_buffer_header_release(buffer);
         }
      }
      else
      {
         /* This port is disabled. Buffer will be a flushed buffer, so
          * return to the pool rather than delivering it.
          */
         mmal_buffer_header_release(buffer);
      }
   }
}