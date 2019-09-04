#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct lro_flow {int dummy; } ;
struct TYPE_3__ {size_t lr_hash_map; struct mbuf* lr_mhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TCP_LRO_FLOW_UNINIT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_1__* lro_flow_list ; 
 int* lro_flow_map ; 

__attribute__((used)) static struct mbuf *
tcp_lro_eject_flow(int flow_id)
{
	struct mbuf *mb = NULL;

	mb = lro_flow_list[flow_id].lr_mhead;
	ASSERT(lro_flow_map[lro_flow_list[flow_id].lr_hash_map] == flow_id);
	lro_flow_map[lro_flow_list[flow_id].lr_hash_map] = TCP_LRO_FLOW_UNINIT;
	bzero(&lro_flow_list[flow_id], sizeof(struct lro_flow));
	
	return mb;
}