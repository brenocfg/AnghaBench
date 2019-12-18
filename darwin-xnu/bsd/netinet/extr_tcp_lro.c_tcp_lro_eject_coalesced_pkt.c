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
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lr_tcphdr; int /*<<< orphan*/ * lr_mtail; struct mbuf* lr_mhead; } ;

/* Variables and functions */
 TYPE_1__* lro_flow_list ; 

__attribute__((used)) static struct mbuf*
tcp_lro_eject_coalesced_pkt(int flow_id)
{
	struct mbuf *mb = NULL;
	mb = lro_flow_list[flow_id].lr_mhead;
	lro_flow_list[flow_id].lr_mhead = 
		lro_flow_list[flow_id].lr_mtail = NULL;
	lro_flow_list[flow_id].lr_tcphdr = NULL;
	return mb;
}