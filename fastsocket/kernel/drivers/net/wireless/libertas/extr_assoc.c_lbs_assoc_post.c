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
struct TYPE_8__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/ * sa_data; } ;
union iwreq_data {TYPE_4__ ap_addr; } ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/ * bssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct lbs_private {int fwrelease; int /*<<< orphan*/  dev; TYPE_3__ curbssparams; int /*<<< orphan*/  tx_pending_len; scalar_t__ numSNRNF; scalar_t__ nextSNRNF; int /*<<< orphan*/  rawNF; int /*<<< orphan*/  rawSNR; scalar_t__** NF; scalar_t__** SNR; int /*<<< orphan*/  connect_status; TYPE_1__* in_progress_assoc_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_associate_response {TYPE_2__ hdr; int /*<<< orphan*/  statuscode; } ;
struct bss_descriptor {int /*<<< orphan*/ * bssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {struct bss_descriptor bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 size_t TYPE_AVG ; 
 size_t TYPE_RXPD ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_assoc_post(struct lbs_private *priv,
			  struct cmd_ds_802_11_associate_response *resp)
{
	int ret = 0;
	union iwreq_data wrqu;
	struct bss_descriptor *bss;
	u16 status_code;

	lbs_deb_enter(LBS_DEB_ASSOC);

	if (!priv->in_progress_assoc_req) {
		lbs_deb_assoc("ASSOC_RESP: no in-progress assoc request\n");
		ret = -1;
		goto done;
	}
	bss = &priv->in_progress_assoc_req->bss;

	/*
	 * Older FW versions map the IEEE 802.11 Status Code in the association
	 * response to the following values returned in resp->statuscode:
	 *
	 *    IEEE Status Code                Marvell Status Code
	 *    0                       ->      0x0000 ASSOC_RESULT_SUCCESS
	 *    13                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    14                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    15                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    16                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    others                  ->      0x0003 ASSOC_RESULT_REFUSED
	 *
	 * Other response codes:
	 *    0x0001 -> ASSOC_RESULT_INVALID_PARAMETERS (unused)
	 *    0x0002 -> ASSOC_RESULT_TIMEOUT (internal timer expired waiting for
	 *                                    association response from the AP)
	 */

	status_code = le16_to_cpu(resp->statuscode);
	if (priv->fwrelease < 0x09000000) {
		switch (status_code) {
		case 0x00:
			break;
		case 0x01:
			lbs_deb_assoc("ASSOC_RESP: invalid parameters\n");
			break;
		case 0x02:
			lbs_deb_assoc("ASSOC_RESP: internal timer "
				"expired while waiting for the AP\n");
			break;
		case 0x03:
			lbs_deb_assoc("ASSOC_RESP: association "
				"refused by AP\n");
			break;
		case 0x04:
			lbs_deb_assoc("ASSOC_RESP: authentication "
				"refused by AP\n");
			break;
		default:
			lbs_deb_assoc("ASSOC_RESP: failure reason 0x%02x "
				" unknown\n", status_code);
			break;
		}
	} else {
		/* v9+ returns the AP's association response */
		lbs_deb_assoc("ASSOC_RESP: failure reason 0x%02x\n", status_code);
	}

	if (status_code) {
		lbs_mac_event_disconnected(priv);
		ret = -1;
		goto done;
	}

	lbs_deb_hex(LBS_DEB_ASSOC, "ASSOC_RESP",
		    (void *) (resp + sizeof (resp->hdr)),
		    le16_to_cpu(resp->hdr.size) - sizeof (resp->hdr));

	/* Send a Media Connected event, according to the Spec */
	priv->connect_status = LBS_CONNECTED;

	/* Update current SSID and BSSID */
	memcpy(&priv->curbssparams.ssid, &bss->ssid, IW_ESSID_MAX_SIZE);
	priv->curbssparams.ssid_len = bss->ssid_len;
	memcpy(priv->curbssparams.bssid, bss->bssid, ETH_ALEN);

	priv->SNR[TYPE_RXPD][TYPE_AVG] = 0;
	priv->NF[TYPE_RXPD][TYPE_AVG] = 0;

	memset(priv->rawSNR, 0x00, sizeof(priv->rawSNR));
	memset(priv->rawNF, 0x00, sizeof(priv->rawNF));
	priv->nextSNRNF = 0;
	priv->numSNRNF = 0;

	netif_carrier_on(priv->dev);
	if (!priv->tx_pending_len)
		netif_wake_queue(priv->dev);

	memcpy(wrqu.ap_addr.sa_data, priv->curbssparams.bssid, ETH_ALEN);
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(priv->dev, SIOCGIWAP, &wrqu, NULL);

done:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}