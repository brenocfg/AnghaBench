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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  service; int /*<<< orphan*/  keep_alive_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_use_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ wfc_client_ipc ; 

void wfc_client_ipc_use_keep_alive(void)
{
   vcos_mutex_lock(&wfc_client_ipc.lock);

   if (!wfc_client_ipc.keep_alive_count++)
      vchiq_use_service(wfc_client_ipc.service);

   vcos_mutex_unlock(&wfc_client_ipc.lock);
}