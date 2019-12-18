#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_1__ MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int MMAL_BUFFER_HEADER_FLAG_EOS ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_event_eos_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static MMAL_STATUS_T null_sink_port_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_BOOL_T eos = buffer->flags & MMAL_BUFFER_HEADER_FLAG_EOS;

   /* Send buffer back */
   buffer->length = 0;
   mmal_port_buffer_header_callback(port, buffer);

   /* Generate EOS events */
   if(eos)
      return mmal_event_eos_send(port);

   return MMAL_SUCCESS;
}