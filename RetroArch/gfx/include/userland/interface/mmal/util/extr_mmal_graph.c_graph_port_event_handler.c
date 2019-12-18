#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ cmd; } ;
struct TYPE_14__ {int /*<<< orphan*/  buffer_size_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  format; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  component; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  int /*<<< orphan*/  MMAL_CONNECTION_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*,char*) ; 
 scalar_t__ MMAL_EVENT_FORMAT_CHANGED ; 
 scalar_t__ MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 scalar_t__ mmal_connection_event_format_changed (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_event_error_send (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* mmal_event_format_changed_get (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_log_dump_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_log_dump_port (TYPE_1__*) ; 

__attribute__((used)) static void graph_port_event_handler(MMAL_CONNECTION_T *connection,
   MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_STATUS_T status;

   LOG_TRACE("port: %s(%p), buffer: %p, event: %4.4s", port->name, port,
             buffer, (char *)&buffer->cmd);

   if (buffer->cmd == MMAL_EVENT_FORMAT_CHANGED && port->type == MMAL_PORT_TYPE_OUTPUT)
   {
      MMAL_EVENT_FORMAT_CHANGED_T *event = mmal_event_format_changed_get(buffer);
      if (event)
      {
         LOG_DEBUG("----------Port format changed----------");
         mmal_log_dump_port(port);
         LOG_DEBUG("-----------------to---------------------");
         mmal_log_dump_format(event->format);
         LOG_DEBUG(" buffers num (opt %i, min %i), size (opt %i, min: %i)",
                   event->buffer_num_recommended, event->buffer_num_min,
                   event->buffer_size_recommended, event->buffer_size_min);
         LOG_DEBUG("----------------------------------------");
      }

      status = mmal_connection_event_format_changed(connection, buffer);
   }

   else
      status = MMAL_SUCCESS; /* FIXME: ignore any other event for now */

   mmal_buffer_header_release(buffer);

   if (status != MMAL_SUCCESS)
      mmal_event_error_send(port->component, status);
}