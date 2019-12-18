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
struct TYPE_2__ {scalar_t__ refcount; int /*<<< orphan*/  lock; scalar_t__ service; int /*<<< orphan*/  waitpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/  vchiq_remove_service (scalar_t__) ; 
 int /*<<< orphan*/  vchiq_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ wfc_client_ipc ; 
 int /*<<< orphan*/  wfc_client_ipc_destroy_waitpool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wfc_client_ipc_once ; 
 int /*<<< orphan*/  wfc_client_ipc_vchiq_instance ; 

bool wfc_client_ipc_deinit(void)
{
   bool service_destroyed = false;

   vcos_once(&wfc_client_ipc_once, init_once);

   vcos_mutex_lock(&wfc_client_ipc.lock);

   if (!wfc_client_ipc.refcount)
   {
      /* Never initialised */
      goto completed;
   }

   if (--wfc_client_ipc.refcount != 0)
   {
      /* Still in use so don't do anything */
      goto completed;
   }

   vcos_log_trace("%s: starting deinitialisation", VCOS_FUNCTION);

   /* Last reference dropped, tear down service */
   wfc_client_ipc_destroy_waitpool(&wfc_client_ipc.waitpool);
   vchiq_remove_service(wfc_client_ipc.service);
   vchiq_shutdown(wfc_client_ipc_vchiq_instance);
   vcos_log_unregister(VCOS_LOG_CATEGORY);

   wfc_client_ipc.service = 0;

   service_destroyed = true;

completed:
   vcos_mutex_unlock(&wfc_client_ipc.lock);

   return service_destroyed;
}