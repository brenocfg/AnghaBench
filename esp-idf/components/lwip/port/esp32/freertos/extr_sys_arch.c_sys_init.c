#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_vfs_lwip_sockets_register () ; 
 int /*<<< orphan*/  g_lwip_protect_mutex ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sys_mutex_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_thread_sem_free ; 
 int /*<<< orphan*/  sys_thread_sem_key ; 

void
sys_init(void)
{
  if (ERR_OK != sys_mutex_new(&g_lwip_protect_mutex)) {
    ESP_LOGE(TAG, "sys_init: failed to init lwip protect mutex\n");
  }

  // Create the pthreads key for the per-thread semaphore storage
  pthread_key_create(&sys_thread_sem_key, sys_thread_sem_free);

  esp_vfs_lwip_sockets_register();
}