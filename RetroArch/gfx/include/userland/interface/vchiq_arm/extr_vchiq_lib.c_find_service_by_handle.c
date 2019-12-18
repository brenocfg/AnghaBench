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
struct TYPE_4__ {scalar_t__ lib_handle; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  scalar_t__ VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 TYPE_1__* handle_to_service (scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_info (char*,scalar_t__) ; 

__attribute__((used)) static VCHIQ_SERVICE_T *
find_service_by_handle(VCHIQ_SERVICE_HANDLE_T handle)
{
   VCHIQ_SERVICE_T *service;

   service = handle_to_service(handle);
   if (service && (service->lib_handle != handle))
      service = NULL;

   if (!service)
      vcos_log_info("Invalid service handle 0x%x", handle);

   return service;
}