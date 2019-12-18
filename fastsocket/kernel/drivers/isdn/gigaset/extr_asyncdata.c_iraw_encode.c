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
struct sk_buff {int len; unsigned char* data; } ;

/* Variables and functions */
 unsigned char DLE_FLAG ; 
 unsigned char bitrev8 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *iraw_encode(struct sk_buff *skb, int head, int tail)
{
	struct sk_buff *iraw_skb;
	unsigned char c;
	unsigned char *cp;
	int len;

	/* worst case: every byte must be stuffed */
	iraw_skb = dev_alloc_skb(2*skb->len + tail + head);
	if (!iraw_skb) {
		dev_kfree_skb(skb);
		return NULL;
	}
	skb_reserve(iraw_skb, head);

	cp = skb->data;
	len = skb->len;
	while (len--) {
		c = bitrev8(*cp++);
		if (c == DLE_FLAG)
			*(skb_put(iraw_skb, 1)) = c;
		*(skb_put(iraw_skb, 1)) = c;
	}
	dev_kfree_skb(skb);
	return iraw_skb;
}