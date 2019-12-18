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
struct xt_target_param {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * nfct; int /*<<< orphan*/  nfctinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  ct_general; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_NEW ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  nf_conntrack_get (int /*<<< orphan*/ *) ; 
 TYPE_1__ nf_conntrack_untracked ; 

__attribute__((used)) static unsigned int
notrack_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	/* Previously seen (loopback)? Ignore. */
	if (skb->nfct != NULL)
		return XT_CONTINUE;

	/* Attach fake conntrack entry.
	   If there is a real ct entry correspondig to this packet,
	   it'll hang aroun till timing out. We don't deal with it
	   for performance reasons. JK */
	skb->nfct = &nf_conntrack_untracked.ct_general;
	skb->nfctinfo = IP_CT_NEW;
	nf_conntrack_get(skb->nfct);

	return XT_CONTINUE;
}