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
struct TYPE_2__ {scalar_t__ prov_state; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_PROV_STATE_STARTING ; 
 scalar_t__ WIFI_PROV_STATE_STOPPING ; 
 int /*<<< orphan*/  protocomm_remove_endpoint (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

void wifi_prov_mgr_endpoint_unregister(const char *ep_name)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return;
    }

    ACQUIRE_LOCK(prov_ctx_lock);
    if (prov_ctx &&
        prov_ctx->prov_state > WIFI_PROV_STATE_STARTING &&
        prov_ctx->prov_state < WIFI_PROV_STATE_STOPPING) {
        protocomm_remove_endpoint(prov_ctx->pc, ep_name);
    }
    RELEASE_LOCK(prov_ctx_lock);
}