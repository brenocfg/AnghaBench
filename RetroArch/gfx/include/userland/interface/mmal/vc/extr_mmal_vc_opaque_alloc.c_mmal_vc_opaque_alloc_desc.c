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
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  header; int /*<<< orphan*/  description; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ mmal_worker_opaque_allocator ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_OPAQUE_IMAGE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WORKER_OPAQUE_ALLOCATOR_DESC ; 
 int /*<<< orphan*/  MMAL_WORKER_OPAQUE_MEM_ALLOC ; 
 int /*<<< orphan*/  mmal_vc_get_client () ; 
 scalar_t__ mmal_vc_sendwait_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_safe_strcpy (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

MMAL_OPAQUE_IMAGE_HANDLE_T mmal_vc_opaque_alloc_desc(const char *description)
{
   MMAL_STATUS_T ret;
   MMAL_OPAQUE_IMAGE_HANDLE_T h = 0;
   mmal_worker_opaque_allocator msg;
   size_t len = sizeof(msg);
   msg.op = MMAL_WORKER_OPAQUE_MEM_ALLOC;
   vcos_safe_strcpy(msg.description, description, sizeof(msg.description), 0);
   ret = mmal_vc_sendwait_message(mmal_vc_get_client(),
                                  &msg.header, sizeof(msg),
                                  MMAL_WORKER_OPAQUE_ALLOCATOR_DESC,
                                  &msg, &len, MMAL_FALSE);
   if (ret == MMAL_SUCCESS)
   {
      h = msg.handle;
   }
   return h;
}