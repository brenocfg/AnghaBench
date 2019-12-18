#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_T ;
typedef  int VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_2__ {int /*<<< orphan*/ * services; } ;

/* Variables and functions */
 int VCHIQ_MAX_INSTANCE_SERVICES ; 
 TYPE_1__ vchiq_instance ; 

__attribute__((used)) static inline VCHIQ_SERVICE_T *
handle_to_service(VCHIQ_SERVICE_HANDLE_T handle)
{
   return &vchiq_instance.services[handle & (VCHIQ_MAX_INSTANCE_SERVICES - 1)];
}