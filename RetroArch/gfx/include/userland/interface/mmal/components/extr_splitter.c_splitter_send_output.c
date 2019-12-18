#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* module; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_EAGAIN ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_buffer_header_replicate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T splitter_send_output(MMAL_BUFFER_HEADER_T *buffer, MMAL_PORT_T *out_port)
{
   MMAL_BUFFER_HEADER_T *out;
   MMAL_STATUS_T status;

   /* Get a buffer header from output port */
   out = mmal_queue_get(out_port->priv->module->queue);
   if (!out)
      return MMAL_EAGAIN;

   /* Copy our input buffer header */
   status = mmal_buffer_header_replicate(out, buffer);
   if (status != MMAL_SUCCESS)
      goto error;

   /* Send buffer back */
   mmal_port_buffer_header_callback(out_port, out);
   return MMAL_SUCCESS;

 error:
   mmal_queue_put_back(out_port->priv->module->queue, out);
   return status;
}