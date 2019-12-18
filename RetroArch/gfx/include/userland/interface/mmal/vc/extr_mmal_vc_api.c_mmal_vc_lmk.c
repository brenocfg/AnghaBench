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
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  reply ;
struct TYPE_3__ {int /*<<< orphan*/  header; int /*<<< orphan*/  alloc_size; } ;
typedef  TYPE_1__ mmal_worker_lmk ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_WORKER_LMK ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 int /*<<< orphan*/  mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_vc_lmk(uint32_t alloc_size)
{
   MMAL_STATUS_T status;
   mmal_worker_lmk req;
   mmal_worker_lmk reply;
   size_t len = sizeof(reply);

   req.alloc_size = alloc_size;

   status = mmal_vc_sendwait_message(mmal_vc_get_client(),
                                     &req.header, sizeof(req),
                                     MMAL_WORKER_LMK,
                                     &reply, &len, MMAL_FALSE);
   return status;
}