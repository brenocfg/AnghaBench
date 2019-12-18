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
struct sk_buff {scalar_t__ len; scalar_t__ tail; scalar_t__ transport_header; } ;
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 scalar_t__ WR_LEN ; 
 unsigned int flits_to_desc (scalar_t__) ; 
 scalar_t__ sgl_len (unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 

__attribute__((used)) static inline unsigned int calc_tx_descs_ofld(const struct sk_buff *skb)
{
	unsigned int flits, cnt;

	if (skb->len <= WR_LEN)
		return 1;	/* packet fits as immediate data */

	flits = skb_transport_offset(skb) / 8;	/* headers */
	cnt = skb_shinfo(skb)->nr_frags;
	if (skb->tail != skb->transport_header)
		cnt++;
	return flits_to_desc(flits + sgl_len(cnt));
}