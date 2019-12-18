#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_8__ {int preview_stop; int /*<<< orphan*/  preview_queue; } ;
typedef  TYPE_1__ RASPITEX_STATE ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void preview_output_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buf)
{
   RASPITEX_STATE *state = (RASPITEX_STATE*) port->userdata;

   if (buf->length == 0)
   {
      vcos_log_trace("%s: zero-length buffer => EOS", port->name);
      state->preview_stop = 1;
      mmal_buffer_header_release(buf);
   }
   else if (buf->data == NULL)
   {
      vcos_log_trace("%s: zero buffer handle", port->name);
      mmal_buffer_header_release(buf);
   }
   else
   {
      /* Enqueue the preview frame for rendering and return to
       * avoid blocking MMAL core.
       */
      mmal_queue_put(state->preview_queue, buf);
   }
}