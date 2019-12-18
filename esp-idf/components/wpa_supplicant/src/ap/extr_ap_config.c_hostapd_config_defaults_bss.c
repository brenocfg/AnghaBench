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
struct hostapd_bss_config {int auth_algs; int wep_rekeying_period; int broadcast_key_idx_min; int broadcast_key_idx_max; int wpa_group_rekey; int wpa_gmk_rekey; int dtim_period; int ap_max_inactivity; int max_listen_interval; int assoc_sa_query_max_timeout; int assoc_sa_query_retry_timeout; int eap_fast_prov; int pac_key_lifetime; int pac_key_refresh_time; int wmm_enabled; int ft_over_ds; int /*<<< orphan*/  eapol_version; int /*<<< orphan*/  max_num_sta; scalar_t__ rsn_pairwise; void* wpa_group; void* wpa_pairwise; int /*<<< orphan*/  wpa_key_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_VERSION ; 
 int /*<<< orphan*/  MAX_STA_COUNT ; 
 int WPA_AUTH_ALG_OPEN ; 
 int WPA_AUTH_ALG_SHARED ; 
 void* WPA_CIPHER_TKIP ; 
 int /*<<< orphan*/  WPA_KEY_MGMT_PSK ; 

void hostapd_config_defaults_bss(struct hostapd_bss_config *bss)
{
    bss->auth_algs = WPA_AUTH_ALG_OPEN | WPA_AUTH_ALG_SHARED;

    bss->wep_rekeying_period = 300;
    /* use key0 in individual key and key1 in broadcast key */
    bss->broadcast_key_idx_min = 1;
    bss->broadcast_key_idx_max = 2;

    bss->wpa_group_rekey = 600;
    bss->wpa_gmk_rekey = 86400;
    bss->wpa_key_mgmt = WPA_KEY_MGMT_PSK;
    bss->wpa_pairwise = WPA_CIPHER_TKIP;
    bss->wpa_group = WPA_CIPHER_TKIP;
    bss->rsn_pairwise = 0;

    bss->max_num_sta = MAX_STA_COUNT;

    bss->dtim_period = 2;

    bss->ap_max_inactivity = 5*60;  //AP_MAX_INACTIVITY;
    bss->eapol_version = EAPOL_VERSION;

    bss->max_listen_interval = 65535;

#ifdef CONFIG_IEEE80211W
    bss->assoc_sa_query_max_timeout = 1000;
    bss->assoc_sa_query_retry_timeout = 201;
#endif /* CONFIG_IEEE80211W */
#ifdef EAP_SERVER_FAST
     /* both anonymous and authenticated provisioning */
    bss->eap_fast_prov = 3;
    bss->pac_key_lifetime = 7 * 24 * 60 * 60;
    bss->pac_key_refresh_time = 1 * 24 * 60 * 60;
#endif /* EAP_SERVER_FAST */

    /* Set to -1 as defaults depends on HT in setup */
    bss->wmm_enabled = -1;

#ifdef CONFIG_IEEE80211R
    bss->ft_over_ds = 1;
#endif /* CONFIG_IEEE80211R */

}