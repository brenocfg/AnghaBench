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
struct sk_buff {scalar_t__ len; } ;
struct cpl_tx_pkt {int dummy; } ;
struct TYPE_2__ {scalar_t__ gso_size; scalar_t__ nr_frags; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int) ; 
 scalar_t__ is_eth_imm (struct sk_buff const*) ; 
 int sgl_len (scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static inline unsigned int calc_tx_flits(const struct sk_buff *skb)
{
	unsigned int flits;

	if (is_eth_imm(skb))
		return DIV_ROUND_UP(skb->len + sizeof(struct cpl_tx_pkt), 8);

	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1) + 4;
	if (skb_shinfo(skb)->gso_size)
		flits += 2;
	return flits;
}