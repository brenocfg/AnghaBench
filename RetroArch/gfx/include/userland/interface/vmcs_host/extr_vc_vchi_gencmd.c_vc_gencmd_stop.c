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
typedef  size_t int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  message_available_event; int /*<<< orphan*/  lock; scalar_t__ initialised; int /*<<< orphan*/ * open_handle; scalar_t__ num_connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ gencmd_client ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 int /*<<< orphan*/  use_gencmd_service () ; 
 size_t vchi_service_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void vc_gencmd_stop () {
   // Assume a "power down" gencmd has been sent and the lock is held. There will
   // be no response so this should be called instead.
   int32_t success,i;

   if (!gencmd_client.initialised)
      return;

   if(lock_obtain() == 0)
   {
      use_gencmd_service();

      for(i = 0; i< (int32_t)gencmd_client.num_connections; i++) {
         success = vchi_service_close( gencmd_client.open_handle[i]);
         assert(success == 0);
      }

      gencmd_client.initialised = 0;

      lock_release();

      vcos_mutex_delete(&gencmd_client.lock);
      vcos_event_delete(&gencmd_client.message_available_event);
   }
}