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
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_3__ {scalar_t__ high_priority; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_khhn_service ; 
 int /*<<< orphan*/  vchiq_khrn_service ; 

__attribute__((used)) static VCHIQ_SERVICE_HANDLE_T get_handle(CLIENT_THREAD_STATE_T *thread)
{
   VCHIQ_SERVICE_HANDLE_T result = (thread->high_priority ? vchiq_khhn_service : vchiq_khrn_service);
   	return result;
}