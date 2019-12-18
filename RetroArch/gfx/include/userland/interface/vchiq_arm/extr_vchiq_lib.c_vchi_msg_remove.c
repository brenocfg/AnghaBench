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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int peek_size; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

int32_t
vchi_msg_remove( VCHI_SERVICE_HANDLE_T handle )
{
   VCHI_SERVICE_T *service = find_service_by_handle(handle);

   if (!service)
      return VCHIQ_ERROR;

   /* Why would you call vchi_msg_remove without calling vchi_msg_peek first? */
   vcos_assert(service->peek_size >= 0);

   /* Invalidate the content but reuse the buffer */
   service->peek_size = -1;

   return 0;
}