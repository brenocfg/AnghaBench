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
struct sk_buff {int /*<<< orphan*/  tail; void* data; } ;

/* Variables and functions */
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ QLGE_SB_PAD ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,unsigned int) ; 

__attribute__((used)) static void ql_realign_skb(struct sk_buff *skb, int len)
{
	void *temp_addr = skb->data;

	/* Undo the skb_reserve(skb,32) we did before
	 * giving to hardware, and realign data on
	 * a 2-byte boundary.
	 */
	skb->data -= QLGE_SB_PAD - NET_IP_ALIGN;
	skb->tail -= QLGE_SB_PAD - NET_IP_ALIGN;
	skb_copy_to_linear_data(skb, temp_addr,
		(unsigned int)len);
}