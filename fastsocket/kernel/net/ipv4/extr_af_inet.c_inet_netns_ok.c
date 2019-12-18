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
struct net_protocol {int netns_ok; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/ * inet_protos ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ net_eq (struct net*,int /*<<< orphan*/ *) ; 
 struct net_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int inet_netns_ok(struct net *net, int protocol)
{
	int hash;
	const struct net_protocol *ipprot;

	if (net_eq(net, &init_net))
		return 1;

	hash = protocol & (MAX_INET_PROTOS - 1);
	ipprot = rcu_dereference(inet_protos[hash]);

	if (ipprot == NULL)
		/* raw IP is OK */
		return 1;
	return ipprot->netns_ok;
}