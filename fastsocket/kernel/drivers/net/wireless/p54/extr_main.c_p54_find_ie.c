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
struct TYPE_3__ {scalar_t__ variable; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  mgmt ;

/* Variables and functions */

u8 *p54_find_ie(struct sk_buff *skb, u8 ie)
{
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	u8 *pos, *end;

	if (skb->len <= sizeof(mgmt))
		return NULL;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = skb->data + skb->len;
	while (pos < end) {
		if (pos + 2 + pos[1] > end)
			return NULL;

		if (pos[0] == ie)
			return pos;

		pos += 2 + pos[1];
	}
	return NULL;
}