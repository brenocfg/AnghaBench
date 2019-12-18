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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {unsigned int handle; scalar_t__ status; int /*<<< orphan*/  header; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ mmal_worker_opaque_allocator ;
typedef  scalar_t__ MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_OPAQUE_ALLOCATOR ; 
 int /*<<< orphan*/  MMAL_WORKER_OPAQUE_MEM_ACQUIRE ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_vc_opaque_acquire(unsigned int handle)
{
   MMAL_STATUS_T ret;
   mmal_worker_opaque_allocator msg;
   size_t len = sizeof(msg);
   msg.handle = handle;
   msg.op = MMAL_WORKER_OPAQUE_MEM_ACQUIRE;
   ret = mmal_vc_sendwait_message(mmal_vc_get_client(),
                                  &msg.header, sizeof(msg),
                                  MMAL_WORKER_OPAQUE_ALLOCATOR,
                                  &msg, &len, MMAL_FALSE);
   if (ret == MMAL_SUCCESS)
      ret = msg.status;
   return ret;
}