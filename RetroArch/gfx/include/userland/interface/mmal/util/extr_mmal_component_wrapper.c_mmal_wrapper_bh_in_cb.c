#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_2__*) ; 

__attribute__((used)) static void mmal_wrapper_bh_in_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_PARAM_UNUSED(port);
   LOG_TRACE("(%s)%p,%p,%p,%i", port->name, port, buffer, buffer->data, (int)buffer->length);

   /* We're done with the buffer, just recycle it */
   mmal_buffer_header_release(buffer);
}