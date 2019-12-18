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
struct eap_sm {int current_identifier; int /*<<< orphan*/ * ssl_ctx; int /*<<< orphan*/  ownaddr; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  SIG_WPA2_MAX ; 
 int /*<<< orphan*/  WIFI_IF_STA ; 
 int /*<<< orphan*/  WPA2_ENT_EAP_STATE_NOT_START ; 
 int /*<<< orphan*/  WPA2_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  eap_peer_blob_deinit (struct eap_sm*) ; 
 int eap_peer_blob_init (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_peer_config_deinit (struct eap_sm*) ; 
 int eap_peer_config_init (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_peer_sm_deinit () ; 
 int /*<<< orphan*/  esp_wifi_get_macaddr_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eap_sm* gEapSm ; 
 int /*<<< orphan*/  g_wpa_private_key_passwd ; 
 int /*<<< orphan*/  g_wpa_private_key_passwd_len ; 
 int /*<<< orphan*/  os_free (struct eap_sm*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  s_wifi_wpa2_sync_sem ; 
 int /*<<< orphan*/  s_wpa2_data_lock ; 
 int /*<<< orphan*/  s_wpa2_queue ; 
 int /*<<< orphan*/  s_wpa2_task_hdl ; 
 int /*<<< orphan*/ * tls_init () ; 
 int /*<<< orphan*/  wpa2_rxq_init () ; 
 int /*<<< orphan*/  wpa2_set_eap_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa2_task ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xSemaphoreCreateCounting (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreCreateRecursiveMutex () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_peer_sm_init(void)
{
    int ret = 0;
    struct eap_sm *sm;

    if (gEapSm) {
        wpa_printf(MSG_ERROR, "WPA2: wpa2 sm not null, deinit it");
        eap_peer_sm_deinit();
    }

    sm = (struct eap_sm *)os_zalloc(sizeof(*sm));
    if (sm == NULL) {
        return ESP_ERR_NO_MEM;
    }

    s_wpa2_data_lock = xSemaphoreCreateRecursiveMutex();
    if (!s_wpa2_data_lock) {
        wpa_printf(MSG_ERROR, "wpa2 eap_peer_sm_init: failed to alloc data lock");
        return ESP_ERR_NO_MEM;
    }

    wpa2_set_eap_state(WPA2_ENT_EAP_STATE_NOT_START);
    sm->current_identifier = 0xff;
    esp_wifi_get_macaddr_internal(WIFI_IF_STA, sm->ownaddr);
    ret = eap_peer_blob_init(sm);
    if (ret) {
        wpa_printf(MSG_ERROR, "eap_peer_blob_init failed\n");
        os_free(sm);
        return ESP_FAIL;
    }

    ret = eap_peer_config_init(sm, g_wpa_private_key_passwd, g_wpa_private_key_passwd_len);
    if (ret) {
        wpa_printf(MSG_ERROR, "eap_peer_config_init failed\n");
        eap_peer_blob_deinit(sm);
        os_free(sm);
        return ESP_FAIL;
    }

    sm->ssl_ctx = tls_init();
    if (sm->ssl_ctx == NULL) {
        wpa_printf(MSG_WARNING, "SSL: Failed to initialize TLS "
                   "context.");
        eap_peer_blob_deinit(sm);
        eap_peer_config_deinit(sm);
        os_free(sm);
        return ESP_FAIL;
    }

    wpa2_rxq_init();

    gEapSm = sm;
#ifdef USE_WPA2_TASK
    s_wpa2_queue = xQueueCreate(SIG_WPA2_MAX, sizeof( void * ) );
    xTaskCreate(wpa2_task, "wpa2T", WPA2_TASK_STACK_SIZE, NULL, 2, s_wpa2_task_hdl);
    s_wifi_wpa2_sync_sem = xSemaphoreCreateCounting(1, 0);
    if (!s_wifi_wpa2_sync_sem) {
        wpa_printf(MSG_ERROR, "WPA2: failed create wifi wpa2 task sync sem");
        return ESP_FAIL;
    }

    wpa_printf(MSG_INFO, "wpa2_task prio:%d, stack:%d\n", 2, WPA2_TASK_STACK_SIZE);

#endif
    return ESP_OK;
}