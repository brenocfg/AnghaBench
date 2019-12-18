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
struct sk_buff {unsigned int network_header; } ;

/* Variables and functions */
 unsigned int nf_bridge_encap_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static inline void nf_bridge_push_encap_header(struct sk_buff *skb)
{
	unsigned int len = nf_bridge_encap_header_len(skb);

	skb_push(skb, len);
	skb->network_header -= len;
}