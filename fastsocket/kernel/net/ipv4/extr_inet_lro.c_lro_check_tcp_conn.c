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
struct tcphdr {scalar_t__ source; scalar_t__ dest; } ;
struct net_lro_desc {TYPE_2__* tcph; TYPE_1__* iph; } ;
struct iphdr {scalar_t__ saddr; scalar_t__ daddr; } ;
struct TYPE_4__ {scalar_t__ source; scalar_t__ dest; } ;
struct TYPE_3__ {scalar_t__ saddr; scalar_t__ daddr; } ;

/* Variables and functions */

__attribute__((used)) static int lro_check_tcp_conn(struct net_lro_desc *lro_desc,
			      struct iphdr *iph,
			      struct tcphdr *tcph)
{
	if ((lro_desc->iph->saddr != iph->saddr)
	    || (lro_desc->iph->daddr != iph->daddr)
	    || (lro_desc->tcph->source != tcph->source)
	    || (lro_desc->tcph->dest != tcph->dest))
		return -1;
	return 0;
}