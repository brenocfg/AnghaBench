#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  mmal_worker_msg_header ;
struct TYPE_3__ {unsigned int time; } ;
typedef  TYPE_1__ mmal_worker_drm_get_time_reply ;
typedef  scalar_t__ MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_DRM_GET_TIME ; 
 int /*<<< orphan*/  mmal_vc_deinit () ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_init () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 

int mmal_vc_drm_get_time(unsigned int * time)
{
   MMAL_STATUS_T status;
   mmal_worker_msg_header req;
   mmal_worker_drm_get_time_reply reply;
   size_t len = sizeof(reply);
   status = mmal_vc_init();
   if (status != MMAL_SUCCESS) return status;
   status = mmal_vc_sendwait_message(mmal_vc_get_client(),
                                     &req, sizeof(req),
                                     MMAL_WORKER_DRM_GET_TIME,
                                     &reply, &len, MMAL_FALSE);
   *time = reply.time;
   mmal_vc_deinit();
   return status;
}