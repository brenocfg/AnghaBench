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
typedef  size_t uint32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_2__ {int initialised; size_t num_connections; int /*<<< orphan*/ * client_handle; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__ dispmanx_client ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void lock_obtain (void) {
   VCOS_STATUS_T status;
   uint32_t i;
   vcos_assert(dispmanx_client.initialised);
   status = vcos_mutex_lock( &dispmanx_client.lock );
   if(dispmanx_client.initialised)
   {
      for (i=0; i<dispmanx_client.num_connections; i++) {
         vchi_service_use(dispmanx_client.client_handle[i]);
      }
   }
   vcos_assert(status == VCOS_SUCCESS);
}