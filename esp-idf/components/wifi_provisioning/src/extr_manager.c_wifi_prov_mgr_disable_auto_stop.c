#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int no_auto_stop; } ;
struct TYPE_5__ {TYPE_1__ capabilities; } ;
struct TYPE_6__ {scalar_t__ prov_state; int /*<<< orphan*/  cleanup_delay; TYPE_2__ mgr_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ WIFI_PROV_STATE_IDLE ; 
 TYPE_3__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

esp_err_t wifi_prov_mgr_disable_auto_stop(uint32_t cleanup_delay)
{
    if (!prov_ctx_lock) {
        ESP_LOGE(TAG, "Provisioning manager not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = ESP_FAIL;
    ACQUIRE_LOCK(prov_ctx_lock);

    if (prov_ctx && prov_ctx->prov_state == WIFI_PROV_STATE_IDLE) {
        prov_ctx->mgr_info.capabilities.no_auto_stop = true;
        prov_ctx->cleanup_delay = cleanup_delay;
        ret = ESP_OK;
    } else {
        ret = ESP_ERR_INVALID_STATE;
    }

    RELEASE_LOCK(prov_ctx_lock);
    return ret;
}