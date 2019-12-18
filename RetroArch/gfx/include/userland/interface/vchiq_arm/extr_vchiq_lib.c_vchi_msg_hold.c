#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int peek_size; int /*<<< orphan*/ * peek_buf; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
struct TYPE_7__ {int /*<<< orphan*/ * service; int /*<<< orphan*/ * message; } ;
typedef  TYPE_2__ VCHI_HELD_MSG_T ;
typedef  int /*<<< orphan*/  VCHI_FLAGS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int fill_peek_buf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 

int32_t
vchi_msg_hold( VCHI_SERVICE_HANDLE_T handle,
   void **data,
   uint32_t *msg_size,
   VCHI_FLAGS_T flags,
   VCHI_HELD_MSG_T *message_handle )
{
   VCHI_SERVICE_T *service = find_service_by_handle(handle);
   int ret;

   if (!service)
      return VCHIQ_ERROR;

   ret = fill_peek_buf(service, flags);

   if (ret == 0)
   {
      *data = service->peek_buf;
      *msg_size = service->peek_size;

      message_handle->message = service->peek_buf;
      message_handle->service = NULL;

      service->peek_size = -1;
      service->peek_buf = NULL;
   }

   return 0;
}