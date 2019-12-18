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
struct sk_buff {int len; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int isdn_ppp_strip_proto(struct sk_buff *skb) 
{
	int proto;
	
	if (skb->len < 1)
		return -1;

	if (skb->data[0] & 0x1) {
		// protocol field is compressed
		proto = skb->data[0];
		skb_pull(skb, 1);
	} else {
		if (skb->len < 2)
			return -1;
		proto = ((int) skb->data[0] << 8) + skb->data[1];
		skb_pull(skb, 2);
	}
	return proto;
}