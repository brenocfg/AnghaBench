#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  peek_size; void* peek_buf; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_FLAGS_T ;

/* Variables and functions */
 int VCHIQ_ERROR ; 
 int fill_peek_buf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 

int32_t
vchi_msg_peek( VCHI_SERVICE_HANDLE_T handle,
   void **data,
   uint32_t *msg_size,
   VCHI_FLAGS_T flags )
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
   }

   return ret;
}