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
struct TYPE_10__ {int cmd; scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; scalar_t__ userdata; } ;
struct TYPE_8__ {int /*<<< orphan*/  sema; } ;
typedef  TYPE_1__ SVP_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,...) ; 
#define  MMAL_EVENT_EOS 129 
#define  MMAL_EVENT_ERROR 128 
 int /*<<< orphan*/  SVP_STOP_EOS ; 
 int /*<<< orphan*/  SVP_STOP_ERROR ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_status_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svp_set_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svp_bh_control_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buf)
{
   SVP_T *svp = (SVP_T *)port->userdata;

   switch (buf->cmd)
   {
   case MMAL_EVENT_EOS:
      LOG_TRACE("%s: EOS", port->name);
      svp_set_stop(svp, SVP_STOP_EOS);
      break;

   case MMAL_EVENT_ERROR:
      LOG_ERROR("%s: MMAL error: %s", port->name,
                mmal_status_to_string(*(MMAL_STATUS_T *)buf->data));
      svp_set_stop(svp, SVP_STOP_ERROR);
      break;

   default:
      LOG_TRACE("%s: buf %p, event %4.4s", port->name, buf, (char *)&buf->cmd);
      break;
   }

   mmal_buffer_header_release(buf);

   vcos_semaphore_post(&svp->sema);
}