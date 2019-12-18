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
struct TYPE_2__ {int refcount; int /*<<< orphan*/  lock; scalar_t__ inited; int /*<<< orphan*/  service; int /*<<< orphan*/  waitpool; int /*<<< orphan*/  bulk_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_INVALID ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 TYPE_1__ client ; 
 int /*<<< orphan*/  destroy_waitpool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_vchiq_instance ; 
 int /*<<< orphan*/  vchiq_close_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void mmal_vc_deinit(void)
{
   int count;

   vcos_mutex_lock(&client.lock);
   count = --client.refcount;
   if (count != 0)
   {
      /* Still in use so don't do anything */
      vcos_mutex_unlock(&client.lock);
      return;
   }

   vcos_mutex_delete(&client.bulk_lock);
   destroy_waitpool(&client.waitpool);
   vchiq_close_service(client.service);
   vchiq_shutdown(mmal_vchiq_instance);
   vcos_log_unregister(VCOS_LOG_CATEGORY);

   client.service = VCHIQ_SERVICE_HANDLE_INVALID;
   client.inited = 0;
   vcos_mutex_unlock(&client.lock);
}