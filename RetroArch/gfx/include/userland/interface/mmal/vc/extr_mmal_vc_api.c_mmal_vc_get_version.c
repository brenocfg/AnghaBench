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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {int /*<<< orphan*/  minimum; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ mmal_worker_version ;
typedef  scalar_t__ MMAL_STATUS_T ;

/* Variables and functions */
 scalar_t__ MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_GET_VERSION ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

MMAL_STATUS_T mmal_vc_get_version(uint32_t *major, uint32_t *minor, uint32_t *minimum)
{
   mmal_worker_version msg;
   size_t len = sizeof(msg);
   MMAL_STATUS_T status;

   status = mmal_vc_sendwait_message(mmal_vc_get_client(), &msg.header, sizeof(msg),
                                     MMAL_WORKER_GET_VERSION, &msg, &len, MMAL_FALSE);

   if (status != MMAL_SUCCESS)
      return status;

   if (!vcos_verify(len == sizeof(msg)))
      return MMAL_EINVAL;

   *major = msg.major;
   *minor = msg.minor;
   *minimum = msg.minimum;
   return MMAL_SUCCESS;
}