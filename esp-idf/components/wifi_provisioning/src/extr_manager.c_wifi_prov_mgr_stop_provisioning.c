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
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  prov_ctx_lock ; 
 int /*<<< orphan*/  wifi_prov_mgr_stop_service (int /*<<< orphan*/ ) ; 

void wifi_prov_mgr_stop_provisioning(void)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return;
    }

    ACQUIRE_LOCK(prov_ctx_lock);

    /* Launches task for stopping the provisioning service. This will do one of these:
     * 1) start a task for stopping the provisioning service (returns true)
     * 2) if service was already in the process of termination, this will
     *    wait till the service is stopped (returns false)
     * 3) if service was not running, this will return immediately (returns false)
     */
    wifi_prov_mgr_stop_service(0);

    RELEASE_LOCK(prov_ctx_lock);
}