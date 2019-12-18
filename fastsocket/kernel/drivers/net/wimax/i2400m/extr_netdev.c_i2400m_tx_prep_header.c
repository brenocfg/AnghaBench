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
struct i2400m_pl_data_hdr {scalar_t__ reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static
void i2400m_tx_prep_header(struct sk_buff *skb)
{
	struct i2400m_pl_data_hdr *pl_hdr;
	skb_pull(skb, ETH_HLEN);
	pl_hdr = (struct i2400m_pl_data_hdr *) skb_push(skb, sizeof(*pl_hdr));
	pl_hdr->reserved = 0;
}