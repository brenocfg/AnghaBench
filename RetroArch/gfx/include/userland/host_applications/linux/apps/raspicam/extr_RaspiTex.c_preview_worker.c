#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int (* create_native_window ) (TYPE_3__*) ;int (* gl_init ) (TYPE_3__*) ;int /*<<< orphan*/  (* gl_term ) (TYPE_3__*) ;} ;
struct TYPE_12__ {int preview_stop; TYPE_2__ ops; int /*<<< orphan*/  preview_queue; TYPE_1__* preview_pool; TYPE_4__* preview_port; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_3__ RASPITEX_STATE ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_send_buffer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 
 scalar_t__ preview_process_returned_bufs (TYPE_3__*) ; 
 int stub1 (TYPE_3__*) ; 
 int stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,...) ; 

__attribute__((used)) static void *preview_worker(void *arg)
{
   RASPITEX_STATE* state = arg;
   MMAL_PORT_T *preview_port = state->preview_port;
   MMAL_BUFFER_HEADER_T *buf;
   MMAL_STATUS_T st;
   int rc;

   vcos_log_trace("%s: port %p", VCOS_FUNCTION, preview_port);

   rc = state->ops.create_native_window(state);
   if (rc != 0)
      goto end;

   rc = state->ops.gl_init(state);
   if (rc != 0)
      goto end;

   while (state->preview_stop == 0)
   {
      /* Send empty buffers to camera preview port */
      while ((buf = mmal_queue_get(state->preview_pool->queue)) != NULL)
      {
         st = mmal_port_send_buffer(preview_port, buf);
         if (st != MMAL_SUCCESS)
         {
            vcos_log_error("Failed to send buffer to %s", preview_port->name);
         }
      }
      /* Process returned buffers */
      if (preview_process_returned_bufs(state) != 0)
      {
         vcos_log_error("Preview error. Exiting.");
         state->preview_stop = 1;
      }
   }

end:
   /* Make sure all buffers are returned on exit */
   while ((buf = mmal_queue_get(state->preview_queue)) != NULL)
      mmal_buffer_header_release(buf);

   /* Tear down GL */
   state->ops.gl_term(state);
   vcos_log_trace("Exiting preview worker");
   return NULL;
}