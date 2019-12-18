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
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_deinit_prev_method (struct eap_sm*,char*) ; 
 int /*<<< orphan*/  eap_peer_blob_deinit (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_peer_config_deinit (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_abort (struct eap_sm*) ; 
 struct eap_sm* gEapSm ; 
 int /*<<< orphan*/  os_free (struct eap_sm*) ; 
 int /*<<< orphan*/ * s_wifi_wpa2_sync_sem ; 
 int /*<<< orphan*/ * s_wpa2_data_lock ; 
 int /*<<< orphan*/  s_wpa2_rxq ; 
 int /*<<< orphan*/  tls_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa2_rxq_deinit () ; 
 int /*<<< orphan*/  wpa2_task_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_peer_sm_deinit(void)
{
    struct eap_sm *sm = gEapSm;

    if (sm == NULL) {
        return;
    }

    eap_peer_config_deinit(sm);
    eap_peer_blob_deinit(sm);
    eap_deinit_prev_method(sm, "EAP deinit");
    eap_sm_abort(sm);
    tls_deinit(sm->ssl_ctx);
#ifdef USE_WPA2_TASK
    wpa2_task_delete(0);
#endif

    if (STAILQ_FIRST((&s_wpa2_rxq)) != NULL) {
        wpa2_rxq_deinit();
    }

    if (s_wifi_wpa2_sync_sem) {
        vSemaphoreDelete(s_wifi_wpa2_sync_sem);
    }
    s_wifi_wpa2_sync_sem = NULL;

    if (s_wpa2_data_lock) {
        vSemaphoreDelete(s_wpa2_data_lock);
        s_wpa2_data_lock = NULL;
        wpa_printf(MSG_DEBUG, "wpa2 eap_peer_sm_deinit: free data lock");
    }

    os_free(sm);
    gEapSm = NULL;
}