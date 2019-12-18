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
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_FRAG_TIMEOUT ; 
 int /*<<< orphan*/  inet_frags_init_net (TYPE_2__*) ; 
 int ip6_frags_ns_sysctl_register (struct net*) ; 

__attribute__((used)) static int ipv6_frags_init_net(struct net *net)
{
	net->ipv6.frags.high_thresh = 256 * 1024;
	net->ipv6.frags.low_thresh = 192 * 1024;
	net->ipv6.frags.timeout = IPV6_FRAG_TIMEOUT;

	inet_frags_init_net(&net->ipv6.frags);

	return ip6_frags_ns_sysctl_register(net);
}