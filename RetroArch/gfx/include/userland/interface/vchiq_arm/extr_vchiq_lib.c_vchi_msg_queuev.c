#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_MSG_VECTOR_T ;
typedef  scalar_t__ VCHI_FLAGS_T ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  const* elements; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ VCHIQ_QUEUE_MESSAGE_T ;
typedef  int /*<<< orphan*/  VCHIQ_ELEMENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_QUEUE_MESSAGE ; 
 scalar_t__ VCHI_FLAGS_BLOCK_UNTIL_QUEUED ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_unused (void*) ; 

int32_t
vchi_msg_queuev( VCHI_SERVICE_HANDLE_T handle,
   VCHI_MSG_VECTOR_T * vector,
   uint32_t count,
   VCHI_FLAGS_T flags,
   void *msg_handle )
{
   VCHI_SERVICE_T *service = find_service_by_handle(handle);
   VCHIQ_QUEUE_MESSAGE_T args;
   int ret;

   vcos_unused(msg_handle);

   vcos_assert(flags == VCHI_FLAGS_BLOCK_UNTIL_QUEUED);

   if (!service)
      return VCHIQ_ERROR;

   args.handle = service->handle;
   args.elements = (const VCHIQ_ELEMENT_T *)vector;
   args.count = count;
   RETRY(ret, ioctl(service->fd, VCHIQ_IOC_QUEUE_MESSAGE, &args));

   return ret;
}