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
struct TYPE_2__ {int /*<<< orphan*/  frags; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IP_ADD_STATS_BH (struct net*,int /*<<< orphan*/ ,int) ; 
 int inet_frag_evictor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip4_frags ; 

__attribute__((used)) static void ip_evictor(struct net *net)
{
	int evicted;

	evicted = inet_frag_evictor(&net->ipv4.frags, &ip4_frags);
	if (evicted)
		IP_ADD_STATS_BH(net, IPSTATS_MIB_REASMFAILS, evicted);
}