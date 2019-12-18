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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAP_PACKET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_ERR_INVALID_BSSID ; 
 int esp_wifi_get_assoc_bssid_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpa2_sm_alloc_eapol (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int wpa2_sm_ether_send (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa2_sm_free_eapol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head_u8 (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

int eap_sm_send_eapol(struct eap_sm *sm, struct wpabuf *resp)
{
    size_t outlen;
    int ret;
    u8 *outbuf = NULL;

    u8 bssid[6];
    ret = esp_wifi_get_assoc_bssid_internal(bssid);

    if (ret != 0) {
        wpa_printf(MSG_DEBUG, "bssid is empty \n");
        return WPA_ERR_INVALID_BSSID;
    }

    outbuf = wpa2_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAP_PACKET,
                                 wpabuf_head_u8(resp), wpabuf_len(resp),
                                 &outlen, NULL);
    if (!outbuf) {
        return ESP_ERR_NO_MEM;
    }

    ret = wpa2_sm_ether_send(sm, bssid, ETH_P_EAPOL, outbuf, outlen);
    wpa2_sm_free_eapol(outbuf);
    if (ret) {
        return ESP_FAIL;
    }

    return ESP_OK;
}