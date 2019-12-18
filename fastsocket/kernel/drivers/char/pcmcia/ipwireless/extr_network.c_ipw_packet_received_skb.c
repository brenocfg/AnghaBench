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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 unsigned char PPP_ALLSTATIONS ; 
 unsigned char PPP_UI ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *ipw_packet_received_skb(unsigned char *data,
					       unsigned int length)
{
	struct sk_buff *skb;

	if (length > 2 && data[0] == PPP_ALLSTATIONS && data[1] == PPP_UI) {
		length -= 2;
		data += 2;
	}

	skb = dev_alloc_skb(length + 4);
	skb_reserve(skb, 2);
	memcpy(skb_put(skb, length), data, length);

	return skb;
}