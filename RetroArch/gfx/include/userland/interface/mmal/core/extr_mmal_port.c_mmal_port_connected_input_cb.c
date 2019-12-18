#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ length; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__* priv; } ;
struct TYPE_13__ {TYPE_1__* core; } ;
struct TYPE_12__ {TYPE_3__* connected_port; } ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MMAL_PORT_TYPE_CLOCK ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_port_send_buffer (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void mmal_port_connected_input_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   LOG_TRACE("buffer %p from connected input port %p: data %p, alloc_size %u, length %u",
             buffer, port, buffer->data, buffer->alloc_size, buffer->length);

   /* Clock ports are bi-directional and a buffer coming from an "input"
    * clock port can potentially have valid payload data, in which case
    * it should be sent directly to the connected port. */
   if (port->type == MMAL_PORT_TYPE_CLOCK && buffer->length)
   {
      MMAL_PORT_T* connected_port = port->priv->core->connected_port;
      mmal_port_send_buffer(connected_port, buffer);
      return;
   }

   /* Simply release buffer back into pool for re-use */
   mmal_buffer_header_release(buffer);
}