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
typedef  int u8 ;
struct sk_buff {int* data; int len; } ;

/* Variables and functions */
 scalar_t__ cfg80211_find_vendor_ie (unsigned int,int,int*,int) ; 
 int /*<<< orphan*/  memmove (int*,int const*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static void wl12xx_remove_vendor_ie(struct sk_buff *skb,
					    unsigned int oui, u8 oui_type,
					    int ieoffset)
{
	int len;
	const u8 *next, *end = skb->data + skb->len;
	u8 *ie = (u8 *)cfg80211_find_vendor_ie(oui, oui_type,
					       skb->data + ieoffset,
					       skb->len - ieoffset);
	if (!ie)
		return;
	len = ie[1] + 2;
	next = ie + len;
	memmove(ie, next, end - next);
	skb_trim(skb, skb->len - len);
}