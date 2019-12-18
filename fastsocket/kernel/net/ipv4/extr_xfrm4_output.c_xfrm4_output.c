#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_2__* IPCB (struct sk_buff*) ; 
 int IPSKB_REROUTED ; 
 int NF_HOOK_COND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NF_INET_POST_ROUTING ; 
 int /*<<< orphan*/  PF_INET ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm4_output_finish ; 

int xfrm4_output(struct sk_buff *skb)
{
	return NF_HOOK_COND(PF_INET, NF_INET_POST_ROUTING, skb,
			    NULL, skb_dst(skb)->dev, xfrm4_output_finish,
			    !(IPCB(skb)->flags & IPSKB_REROUTED));
}