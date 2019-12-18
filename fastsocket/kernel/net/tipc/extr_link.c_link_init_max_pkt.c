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
typedef  int u32 ;
struct link {int max_pkt_target; int max_pkt; scalar_t__ max_pkt_probes; TYPE_2__* b_ptr; } ;
struct TYPE_3__ {int mtu; } ;
struct TYPE_4__ {TYPE_1__ publ; } ;

/* Variables and functions */
 int MAX_MSG_SIZE ; 
 int MAX_PKT_DEFAULT ; 

__attribute__((used)) static void link_init_max_pkt(struct link *l_ptr)
{
	u32 max_pkt;

	max_pkt = (l_ptr->b_ptr->publ.mtu & ~3);
	if (max_pkt > MAX_MSG_SIZE)
		max_pkt = MAX_MSG_SIZE;

	l_ptr->max_pkt_target = max_pkt;
	if (l_ptr->max_pkt_target < MAX_PKT_DEFAULT)
		l_ptr->max_pkt = l_ptr->max_pkt_target;
	else
		l_ptr->max_pkt = MAX_PKT_DEFAULT;

	l_ptr->max_pkt_probes = 0;
}