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
struct TYPE_4__ {int high_thresh; int low_thresh; int /*<<< orphan*/  timeout; } ;
struct TYPE_3__ {TYPE_2__ frags; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_FRAG_TIME ; 
 int /*<<< orphan*/  inet_frags_init_net (TYPE_2__*) ; 
 int ip4_frags_ns_ctl_register (struct net*) ; 

__attribute__((used)) static int ipv4_frags_init_net(struct net *net)
{
	/*
	 * Fragment cache limits. We will commit 256K at one time. Should we
	 * cross that limit we will prune down to 192K. This should cope with
	 * even the most extreme cases without allowing an attacker to
	 * measurably harm machine performance.
	 */
	net->ipv4.frags.high_thresh = 256 * 1024;
	net->ipv4.frags.low_thresh = 192 * 1024;
	/*
	 * Important NOTE! Fragment queue must be destroyed before MSL expires.
	 * RFC791 is wrong proposing to prolongate timer each fragment arrival
	 * by TTL.
	 */
	net->ipv4.frags.timeout = IP_FRAG_TIME;

	inet_frags_init_net(&net->ipv4.frags);

	return ip4_frags_ns_ctl_register(net);
}