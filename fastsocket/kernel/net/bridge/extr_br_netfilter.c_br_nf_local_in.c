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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  br_drop_fake_rtable (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_local_in(unsigned int hook, struct sk_buff *skb,
				   const struct net_device *in,
				   const struct net_device *out,
				   int (*okfn)(struct sk_buff *))
{
	br_drop_fake_rtable(skb);
	return NF_ACCEPT;
}