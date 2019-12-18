#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* video_frame_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  video_frame_count; } ;
struct TYPE_10__ {TYPE_1__ stats; int /*<<< orphan*/  queue; TYPE_3__ callbacks; } ;
typedef  TYPE_2__ SVP_T ;
typedef  TYPE_3__ SVP_CALLBACKS_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int SVP_STOP_ERROR ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_4__*) ; 
 TYPE_4__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svp_get_stop (TYPE_2__*) ; 

__attribute__((used)) static void svp_process_returned_bufs(SVP_T *svp)
{
   SVP_CALLBACKS_T *callbacks = &svp->callbacks;
   MMAL_BUFFER_HEADER_T *buf;

   while ((buf = mmal_queue_get(svp->queue)) != NULL)
   {
      if ((svp_get_stop(svp) & SVP_STOP_ERROR) == 0)
      {
         callbacks->video_frame_cb(callbacks->ctx, buf->data);
      }

      svp->stats.video_frame_count++;
      mmal_buffer_header_release(buf);
   }
}