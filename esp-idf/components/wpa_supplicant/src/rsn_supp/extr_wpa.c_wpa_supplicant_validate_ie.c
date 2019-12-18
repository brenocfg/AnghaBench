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
struct wpa_sm {scalar_t__ proto; scalar_t__ rsn_enabled; int /*<<< orphan*/ * ap_rsn_ie; int /*<<< orphan*/  ap_rsn_ie_len; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/ * ap_wpa_ie; int /*<<< orphan*/  ap_wpa_ie_len; } ;
struct wpa_eapol_ie_parse {int /*<<< orphan*/  rsn_ie_len; int /*<<< orphan*/ * rsn_ie; int /*<<< orphan*/  wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_PROTO_WPA ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_compare_rsn_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_report_ie_mismatch (struct wpa_sm*,...) ; 
 scalar_t__ wpa_sm_get_beacon_ie (struct wpa_sm*) ; 

int   wpa_supplicant_validate_ie(struct wpa_sm *sm,
                      const unsigned char *src_addr,
                      struct wpa_eapol_ie_parse *ie)
{
    if (sm->ap_wpa_ie == NULL && sm->ap_rsn_ie == NULL) {
        #ifdef DEBUG_PRINT    
        wpa_printf(MSG_DEBUG, "WPA: No WPA/RSN IE for this AP known. "
               "Trying to get from scan results\n");
        #endif    
        if (wpa_sm_get_beacon_ie(sm) < 0) {
            #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: Could not find AP from "
                   "the scan results");
            #endif    
        } else {
            #ifdef DEBUG_PRINT    
            wpa_printf(MSG_DEBUG, "WPA: Found the current AP from "
                   "updated scan results\n");
            #endif    
        }
    }

    if (ie->wpa_ie == NULL && ie->rsn_ie == NULL &&
        (sm->ap_wpa_ie || sm->ap_rsn_ie)) {
#ifdef DEBUG_PRINT
        wpa_report_ie_mismatch(sm, "IE in 3/4 msg does not match "
                       "with IE in Beacon/ProbeResp (no IE?)",
                       src_addr, ie->wpa_ie, ie->wpa_ie_len,
                       ie->rsn_ie, ie->rsn_ie_len);
#else
        wpa_report_ie_mismatch(sm,
                       src_addr, ie->wpa_ie, ie->wpa_ie_len,
                       ie->rsn_ie, ie->rsn_ie_len);
#endif
        return -1;
    }

    if ((ie->wpa_ie && sm->ap_wpa_ie &&
         (ie->wpa_ie_len != sm->ap_wpa_ie_len ||
         memcmp(ie->wpa_ie, sm->ap_wpa_ie, ie->wpa_ie_len) != 0)) ||
        (ie->rsn_ie && sm->ap_rsn_ie &&
         wpa_compare_rsn_ie(wpa_key_mgmt_ft(sm->key_mgmt),
                sm->ap_rsn_ie, sm->ap_rsn_ie_len,
                ie->rsn_ie, ie->rsn_ie_len))) {
#ifdef DEBUG_PRINT
        wpa_report_ie_mismatch(sm, "IE in 3/4 msg does not match "
                       "with IE in Beacon/ProbeResp",
                       src_addr, ie->wpa_ie, ie->wpa_ie_len,
                       ie->rsn_ie, ie->rsn_ie_len);
#else
        wpa_report_ie_mismatch(sm,
                       src_addr, ie->wpa_ie, ie->wpa_ie_len,
                       ie->rsn_ie, ie->rsn_ie_len);
#endif
        return -1;
    }

    if (sm->proto == WPA_PROTO_WPA &&
        ie->rsn_ie && sm->ap_rsn_ie == NULL && sm->rsn_enabled) {
#ifdef DEBUG_PRINT
        wpa_report_ie_mismatch(sm, "Possible downgrade attack "
                       "detected - RSN was enabled and RSN IE "
                       "was in msg 3/4, but not in "
                       "Beacon/ProbeResp",
                       src_addr, ie->wpa_ie, ie->wpa_ie_len,
                       ie->rsn_ie, ie->rsn_ie_len);
#else
        wpa_report_ie_mismatch(sm,
                               src_addr, ie->wpa_ie, ie->wpa_ie_len,
                               ie->rsn_ie, ie->rsn_ie_len);
#endif
        return -1;
    }

    return 0;
}