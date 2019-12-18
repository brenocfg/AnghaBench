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
struct TYPE_2__ {size_t num_connections; int /*<<< orphan*/  lock; int /*<<< orphan*/ * client_handle; scalar_t__ initialised; } ;

/* Variables and functions */
 TYPE_1__ dispmanx_client ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (scalar_t__) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void lock_release (void) {
   uint32_t i;
   vcos_assert(dispmanx_client.initialised);
   if(dispmanx_client.initialised)
   {
      for (i=0; i<dispmanx_client.num_connections; i++) {
         vchi_service_release(dispmanx_client.client_handle[i]);
      }
   }
   vcos_mutex_unlock( &dispmanx_client.lock );
}