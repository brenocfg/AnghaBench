#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int capabilities; scalar_t__ buffer_size; scalar_t__ buffer_num; int /*<<< orphan*/  name; int /*<<< orphan*/  format; } ;
struct TYPE_18__ {scalar_t__ cmd; } ;
struct TYPE_17__ {TYPE_4__* in; TYPE_4__* out; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {scalar_t__ buffer_size_min; scalar_t__ buffer_num_min; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 scalar_t__ MMAL_EVENT_FORMAT_CHANGED ; 
 int MMAL_PORT_CAPABILITY_SUPPORTS_EVENT_FORMAT_CHANGE ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_buffer_header_acquire (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_connection_reconfigure (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mmal_event_format_changed_get (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_format_full_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_format_commit (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_port_send_buffer (TYPE_4__*,TYPE_3__*) ; 

MMAL_STATUS_T mmal_connection_event_format_changed(MMAL_CONNECTION_T *connection,
   MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_EVENT_FORMAT_CHANGED_T *event;
   MMAL_STATUS_T status;

   LOG_TRACE("%p, %s", connection, connection->name);

   if (buffer->cmd != MMAL_EVENT_FORMAT_CHANGED)
      return MMAL_EINVAL;

   event = mmal_event_format_changed_get(buffer);
   if (!event)
      return MMAL_EINVAL;

   /* If we don't need to recreate our buffers then we can just forward the event
    * to the next component (so it gets configured properly) */
   if ((connection->in->capabilities & MMAL_PORT_CAPABILITY_SUPPORTS_EVENT_FORMAT_CHANGE) &&
       event->buffer_size_min <= connection->out->buffer_size &&
       event->buffer_num_min <= connection->out->buffer_num)
   {
      status = mmal_format_full_copy(connection->out->format, event->format);
      if (status == MMAL_SUCCESS)
         status = mmal_port_format_commit(connection->out);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("format commit failed on port %s(%p) (%i)",
                   connection->out->name, connection->out, status);
         return status;
      }

      mmal_buffer_header_acquire(buffer);
      status = mmal_port_send_buffer(connection->in, buffer);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("buffer send failed on port %s(%p) (%i)",
                   connection->in->name, connection->in, status);
         mmal_buffer_header_release(buffer);
         return status;
      }

      return MMAL_SUCCESS;
   }

   /* Otherwise we have to reconfigure our pipeline */
   return mmal_connection_reconfigure(connection, event->format);
}