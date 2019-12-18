#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  sema; int /*<<< orphan*/  queue; int /*<<< orphan*/  wd_timer; } ;
typedef  TYPE_1__ SVP_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVP_STOP_EOS ; 
 int /*<<< orphan*/  SVP_WATCHDOG_TIMEOUT_MS ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  svp_set_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svp_bh_output_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buf)
{
   SVP_T *svp = (SVP_T *)port->userdata;

   if (buf->length == 0)
   {
      LOG_TRACE("%s: zero-length buffer => EOS", port->name);
      svp_set_stop(svp, SVP_STOP_EOS); // This shouldn't be necessary, but it is ...
      mmal_buffer_header_release(buf);
   }
   else if (buf->data == NULL)
   {
      LOG_ERROR("%s: zero buffer handle", port->name);
      mmal_buffer_header_release(buf);
   }
   else
   {
      /* Reset watchdog timer */
      vcos_timer_set(&svp->wd_timer, SVP_WATCHDOG_TIMEOUT_MS);

      /* Enqueue the decoded frame so we can return quickly to MMAL core */
      mmal_queue_put(svp->queue, buf);
   }

   /* Notify worker */
   vcos_semaphore_post(&svp->sema);
}