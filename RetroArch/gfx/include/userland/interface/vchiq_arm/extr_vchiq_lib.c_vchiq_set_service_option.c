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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_5__ {int value; int /*<<< orphan*/  option; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ VCHIQ_SET_SERVICE_OPTION_T ;
struct TYPE_6__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_SET_SERVICE_OPTION ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 TYPE_2__* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

VCHIQ_STATUS_T
vchiq_set_service_option(VCHIQ_SERVICE_HANDLE_T handle,
   VCHIQ_SERVICE_OPTION_T option, int value)
{
   VCHIQ_SET_SERVICE_OPTION_T args;
   VCHIQ_SERVICE_T *service = find_service_by_handle(handle);
   int ret;

   if (!service)
      return VCHIQ_ERROR;

   args.handle = service->handle;
   args.option = option;
   args.value  = value;

   RETRY(ret, ioctl(service->fd, VCHIQ_IOC_SET_SERVICE_OPTION, &args));

   return (ret >= 0) ? VCHIQ_SUCCESS : VCHIQ_ERROR;
}