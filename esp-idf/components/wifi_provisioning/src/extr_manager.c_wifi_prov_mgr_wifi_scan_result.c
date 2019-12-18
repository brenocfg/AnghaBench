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
typedef  int /*<<< orphan*/  wifi_ap_record_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** ap_list_sorted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 size_t MAX_SCAN_RESULTS ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

const wifi_ap_record_t *wifi_prov_mgr_wifi_scan_result(uint16_t index)
{
    const wifi_ap_record_t *rval = NULL;
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return rval;
    }

    ACQUIRE_LOCK(prov_ctx_lock);
    if (!prov_ctx) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        RELEASE_LOCK(prov_ctx_lock);
        return rval;
    }

    if (index < MAX_SCAN_RESULTS) {
        rval = prov_ctx->ap_list_sorted[index];
    }
    RELEASE_LOCK(prov_ctx_lock);
    return rval;
}