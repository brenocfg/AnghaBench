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
struct TYPE_3__ {int nqueues; } ;
struct TYPE_4__ {TYPE_1__ frags; } ;
struct net {TYPE_2__ ipv6; } ;

/* Variables and functions */

int ip6_frag_nqueues(struct net *net)
{
	return net->ipv6.frags.nqueues;
}