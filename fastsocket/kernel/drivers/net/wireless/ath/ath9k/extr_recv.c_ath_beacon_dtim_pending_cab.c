#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int* data; int len; } ;
struct ieee80211_tim_ie {scalar_t__ dtim_count; int bitmap_ctrl; } ;
struct TYPE_3__ {int* variable; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;

/* Variables and functions */
 int WLAN_EID_TIM ; 

__attribute__((used)) static bool ath_beacon_dtim_pending_cab(struct sk_buff *skb)
{
	/* Check whether the Beacon frame has DTIM indicating buffered bc/mc */
	struct ieee80211_mgmt *mgmt;
	u8 *pos, *end, id, elen;
	struct ieee80211_tim_ie *tim;

	mgmt = (struct ieee80211_mgmt *)skb->data;
	pos = mgmt->u.beacon.variable;
	end = skb->data + skb->len;

	while (pos + 2 < end) {
		id = *pos++;
		elen = *pos++;
		if (pos + elen > end)
			break;

		if (id == WLAN_EID_TIM) {
			if (elen < sizeof(*tim))
				break;
			tim = (struct ieee80211_tim_ie *) pos;
			if (tim->dtim_count != 0)
				break;
			return tim->bitmap_ctrl & 0x01;
		}

		pos += elen;
	}

	return false;
}