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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_extend ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_event_fini_sysctl (struct net*) ; 
 int /*<<< orphan*/  nf_ct_extend_unregister (int /*<<< orphan*/ *) ; 

void nf_conntrack_ecache_fini(struct net *net)
{
	nf_conntrack_event_fini_sysctl(net);
	if (net_eq(net, &init_net))
		nf_ct_extend_unregister(&event_extend);
}