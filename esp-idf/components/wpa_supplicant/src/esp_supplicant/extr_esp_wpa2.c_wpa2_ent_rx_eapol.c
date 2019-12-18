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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee802_1x_hdr {int type; } ;

/* Variables and functions */
 int ESP_OK ; 
#define  IEEE802_1X_TYPE_EAPOL_KEY 131 
#define  IEEE802_1X_TYPE_EAPOL_LOGOFF 130 
#define  IEEE802_1X_TYPE_EAPOL_START 129 
#define  IEEE802_1X_TYPE_EAP_PACKET 128 
 int /*<<< orphan*/  MSG_ERROR ; 
 int eap_sm_rx_eapol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int wpa_sm_rx_eapol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa2_ent_rx_eapol(u8 *src_addr, u8 *buf, u32 len, uint8_t *bssid)
{
    struct ieee802_1x_hdr *hdr;
    int ret = ESP_OK;

    hdr = (struct ieee802_1x_hdr *) buf;

    switch (hdr->type) {
	    case IEEE802_1X_TYPE_EAPOL_START:
	    case IEEE802_1X_TYPE_EAP_PACKET:
	    case IEEE802_1X_TYPE_EAPOL_LOGOFF:
		    ret = eap_sm_rx_eapol(src_addr, buf, len, bssid);
		    break;
	    case IEEE802_1X_TYPE_EAPOL_KEY:
            ret = wpa_sm_rx_eapol(src_addr, buf, len);
		    break;
	    default:
		wpa_printf(MSG_ERROR, "Unknown EAPOL packet type - %d\n", hdr->type);
		    break;
    }

	return ret;
}