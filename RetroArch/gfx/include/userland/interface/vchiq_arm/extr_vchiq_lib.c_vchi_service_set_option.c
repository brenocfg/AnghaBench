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
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ VCHI_SERVICE_T ;
typedef  int VCHI_SERVICE_OPTION_T ;
typedef  int /*<<< orphan*/  VCHI_SERVICE_HANDLE_T ;
struct TYPE_6__ {int value; int /*<<< orphan*/  handle; int /*<<< orphan*/  option; } ;
typedef  TYPE_2__ VCHIQ_SET_SERVICE_OPTION_T ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 int VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_SET_SERVICE_OPTION ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_OPTION_TRACE ; 
#define  VCHI_SERVICE_OPTION_TRACE 128 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int32_t vchi_service_set_option( const VCHI_SERVICE_HANDLE_T handle,
   VCHI_SERVICE_OPTION_T option, int value)
{
   VCHIQ_SET_SERVICE_OPTION_T args;
   VCHI_SERVICE_T *service = find_service_by_handle(handle);
   int ret;

   switch (option)
   {
   case VCHI_SERVICE_OPTION_TRACE:
      args.option = VCHIQ_SERVICE_OPTION_TRACE;
      break;
   default:
      service = NULL;
      break;
   }

   if (!service)
      return VCHIQ_ERROR;

   args.handle = service->handle;
   args.value  = value;

   RETRY(ret, ioctl(service->fd, VCHIQ_IOC_SET_SERVICE_OPTION, &args));

   return ret;
}