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
struct TYPE_2__ {int /*<<< orphan*/  scanning; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

bool wifi_prov_mgr_wifi_scan_finished(void)
{
    bool scan_finished = true;
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return scan_finished;
    }

    ACQUIRE_LOCK(prov_ctx_lock);
    if (!prov_ctx) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        RELEASE_LOCK(prov_ctx_lock);
        return scan_finished;
    }

    scan_finished = !prov_ctx->scanning;
    RELEASE_LOCK(prov_ctx_lock);
    return scan_finished;
}