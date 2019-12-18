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
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_GET_CLIENT_ID ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vchiq_get_client_id(VCHIQ_SERVICE_HANDLE_T handle)
{
   VCHIQ_SERVICE_T *service = find_service_by_handle(handle);

   if (!service)
      return VCHIQ_ERROR;

   return ioctl(service->fd, VCHIQ_IOC_GET_CLIENT_ID, service->handle);
}