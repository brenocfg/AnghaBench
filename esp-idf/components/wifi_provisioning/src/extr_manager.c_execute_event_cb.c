#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* wifi_prov_cb_func_t ) (void*,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  wifi_prov_cb_event_t ;
struct TYPE_5__ {void* user_data; int /*<<< orphan*/  (* event_cb ) (void*,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_7__ {void* user_data; int /*<<< orphan*/  (* event_cb ) (void*,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_6__ {TYPE_1__ scheme_event_handler; TYPE_3__ app_event_handler; } ;
struct TYPE_8__ {TYPE_2__ mgr_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  WIFI_PROV_EVENT ; 
 scalar_t__ esp_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 TYPE_4__* prov_ctx ; 
 int /*<<< orphan*/  prov_ctx_lock ; 

__attribute__((used)) static void execute_event_cb(wifi_prov_cb_event_t event_id, void *event_data, size_t event_data_size)
{
    ESP_LOGD(TAG, "execute_event_cb : %d", event_id);

    if (prov_ctx) {
        wifi_prov_cb_func_t app_cb = prov_ctx->mgr_config.app_event_handler.event_cb;
        void *app_data = prov_ctx->mgr_config.app_event_handler.user_data;

        wifi_prov_cb_func_t scheme_cb = prov_ctx->mgr_config.scheme_event_handler.event_cb;
        void *scheme_data = prov_ctx->mgr_config.scheme_event_handler.user_data;

        /* Release the mutex before executing the callbacks. This is done so that
         * wifi_prov_mgr_event_handler() doesn't stay blocked for the duration */
        RELEASE_LOCK(prov_ctx_lock);

        if (scheme_cb) {
            /* Call scheme specific event handler */
            scheme_cb(scheme_data, event_id, event_data);
        }

        if (app_cb) {
            /* Call application specific event handler */
            app_cb(app_data, event_id, event_data);
        }

        if (esp_event_post(WIFI_PROV_EVENT, event_id,
                           event_data, event_data_size,
                           portMAX_DELAY) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to post event %d to default event loop", event_id);
        }

        ACQUIRE_LOCK(prov_ctx_lock);
    }
}