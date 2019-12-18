#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* userdata; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 TYPE_2__* find_service_by_handle (int /*<<< orphan*/ ) ; 

void *
vchiq_get_service_userdata(VCHIQ_SERVICE_HANDLE_T handle)
{
   VCHIQ_SERVICE_T *service = find_service_by_handle(handle);

   return service ? service->base.userdata : NULL;
}