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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_if_mesh {scalar_t__* ie; int ie_len; } ;
struct TYPE_2__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ const WLAN_EID_RSN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

int mesh_add_rsn_ie(struct ieee80211_sub_if_data *sdata, struct sk_buff *skb)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 len = 0;
	const u8 *data;

	if (!ifmsh->ie || !ifmsh->ie_len)
		return 0;

	/* find RSN IE */
	data = ifmsh->ie;
	while (data < ifmsh->ie + ifmsh->ie_len) {
		if (*data == WLAN_EID_RSN) {
			len = data[1] + 2;
			break;
		}
		data++;
	}

	if (len) {
		if (skb_tailroom(skb) < len)
			return -ENOMEM;
		memcpy(skb_put(skb, len), data, len);
	}

	return 0;
}