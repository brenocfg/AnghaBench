#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct iwl_wipan_noa_notification {TYPE_1__ noa_attribute; scalar_t__ noa_active; } ;
struct iwl_wipan_noa_data {int length; int* data; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  noa_data; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 int WLAN_OUI_TYPE_WFA_P2P ; 
 int WLAN_OUI_WFA ; 
 int /*<<< orphan*/  kfree_rcu (struct iwl_wipan_noa_data*,int /*<<< orphan*/ ) ; 
 struct iwl_wipan_noa_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct iwl_wipan_noa_data*) ; 
 struct iwl_wipan_noa_data* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_head ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static int iwlagn_rx_noa_notification(struct iwl_priv *priv,
				      struct iwl_rx_cmd_buffer *rxb,
				      struct iwl_device_cmd *cmd)
{
	struct iwl_wipan_noa_data *new_data, *old_data;
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_wipan_noa_notification *noa_notif = (void *)pkt->data;

	/* no condition -- we're in softirq */
	old_data = rcu_dereference_protected(priv->noa_data, true);

	if (noa_notif->noa_active) {
		u32 len = le16_to_cpu(noa_notif->noa_attribute.length);
		u32 copylen = len;

		/* EID, len, OUI, subtype */
		len += 1 + 1 + 3 + 1;
		/* P2P id, P2P length */
		len += 1 + 2;
		copylen += 1 + 2;

		new_data = kmalloc(sizeof(*new_data) + len, GFP_ATOMIC);
		if (new_data) {
			new_data->length = len;
			new_data->data[0] = WLAN_EID_VENDOR_SPECIFIC;
			new_data->data[1] = len - 2; /* not counting EID, len */
			new_data->data[2] = (WLAN_OUI_WFA >> 16) & 0xff;
			new_data->data[3] = (WLAN_OUI_WFA >> 8) & 0xff;
			new_data->data[4] = (WLAN_OUI_WFA >> 0) & 0xff;
			new_data->data[5] = WLAN_OUI_TYPE_WFA_P2P;
			memcpy(&new_data->data[6], &noa_notif->noa_attribute,
			       copylen);
		}
	} else
		new_data = NULL;

	rcu_assign_pointer(priv->noa_data, new_data);

	if (old_data)
		kfree_rcu(old_data, rcu_head);

	return 0;
}