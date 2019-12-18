#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {TYPE_2__* priv; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_1__* clock; } ;
struct TYPE_15__ {int /*<<< orphan*/  queue; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_CLOCK_EVENT_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ MMAL_ENOSPC ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_4__ const*,int) ; 
 scalar_t__ mmal_buffer_header_mem_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_unlock (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_3__*,TYPE_5__*) ; 
 TYPE_5__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_status_to_string (scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_forward_event(MMAL_PORT_T *port, const MMAL_CLOCK_EVENT_T *event)
{
   MMAL_STATUS_T status;
   MMAL_BUFFER_HEADER_T *buffer;

   buffer = mmal_queue_get(port->priv->clock->queue);
   if (!buffer)
   {
      LOG_INFO("%s: no free event buffers available for event %4.4s", port->name, (const char*)&event->id);
      return MMAL_ENOSPC;
   }

   status = mmal_buffer_header_mem_lock(buffer);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("failed to lock buffer %s", mmal_status_to_string(status));
      mmal_queue_put_back(port->priv->clock->queue, buffer);
      goto end;
   }
   buffer->length = sizeof(MMAL_CLOCK_EVENT_T);
   memcpy(buffer->data, event, buffer->length);
   mmal_buffer_header_mem_unlock(buffer);

   mmal_port_buffer_header_callback(port, buffer);

end:
   return status;
}