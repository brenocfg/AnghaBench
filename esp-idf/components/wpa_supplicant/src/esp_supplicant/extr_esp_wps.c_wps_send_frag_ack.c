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
struct wps_sm {int dummy; } ;
struct wpabuf {int dummy; } ;
typedef  enum wsc_op_code { ____Placeholder_wsc_op_code } wsc_op_code ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_VENDOR_WFA ; 
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAP_PACKET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WSC_FRAG_ACK ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esp_wifi_get_assoc_bssid_internal (int /*<<< orphan*/ *) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head_u8 (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 
 int /*<<< orphan*/ * wps_sm_alloc_eapol (struct wps_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int wps_sm_ether_send (struct wps_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wps_sm_free_eapol (int /*<<< orphan*/ *) ; 

int wps_send_frag_ack(u8 id)
{
    struct wps_sm *sm = gWpsSm;
    struct wpabuf *eap_buf = NULL;
    u8 bssid[6];
    u8 *buf;
    int len;
    int ret = 0;
    enum wsc_op_code opcode = WSC_FRAG_ACK;

    wpa_printf(MSG_DEBUG, "send frag ack id:%d", id);

    if (!sm) {
        return ESP_FAIL;
    }

    ret = esp_wifi_get_assoc_bssid_internal(bssid);
    if (ret != 0) {
        wpa_printf(MSG_ERROR, "bssid is empty!");
        return ret;
    }

    eap_buf = eap_msg_alloc(EAP_VENDOR_WFA, 0x00000001, 2, EAP_CODE_RESPONSE, id);
    if (!eap_buf) {
        ret = ESP_ERR_NO_MEM;
        goto _err;
    }

    wpabuf_put_u8(eap_buf, opcode);
    wpabuf_put_u8(eap_buf, 0x00); /* flags */

    buf = wps_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAP_PACKET, wpabuf_head_u8(eap_buf), wpabuf_len(eap_buf), (size_t *)&len, NULL);
    if (!buf) {
        ret = ESP_ERR_NO_MEM;
        goto _err;
    }

    ret = wps_sm_ether_send(sm, bssid, ETH_P_EAPOL, buf, len);
    wps_sm_free_eapol(buf);
    if (ret) {
        ret = ESP_ERR_NO_MEM;
        goto _err;
    }

_err:
    wpabuf_free(eap_buf);
    return ret;
}