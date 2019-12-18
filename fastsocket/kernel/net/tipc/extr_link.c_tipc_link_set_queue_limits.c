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
typedef  int u32 ;
struct link {int* queue_limit; } ;

/* Variables and functions */
 size_t CHANGEOVER_PROTOCOL ; 
 size_t CONN_MANAGER ; 
 size_t MSG_FRAGMENTER ; 
 size_t NAME_DISTRIBUTOR ; 
 size_t ROUTE_DISTRIBUTOR ; 
 size_t TIPC_CRITICAL_IMPORTANCE ; 
 size_t TIPC_HIGH_IMPORTANCE ; 
 size_t TIPC_LOW_IMPORTANCE ; 
 size_t TIPC_MEDIUM_IMPORTANCE ; 

void tipc_link_set_queue_limits(struct link *l_ptr, u32 window)
{
	/* Data messages from this node, inclusive FIRST_FRAGM */
	l_ptr->queue_limit[TIPC_LOW_IMPORTANCE] = window;
	l_ptr->queue_limit[TIPC_MEDIUM_IMPORTANCE] = (window / 3) * 4;
	l_ptr->queue_limit[TIPC_HIGH_IMPORTANCE] = (window / 3) * 5;
	l_ptr->queue_limit[TIPC_CRITICAL_IMPORTANCE] = (window / 3) * 6;
	/* Transiting data messages,inclusive FIRST_FRAGM */
	l_ptr->queue_limit[TIPC_LOW_IMPORTANCE + 4] = 300;
	l_ptr->queue_limit[TIPC_MEDIUM_IMPORTANCE + 4] = 600;
	l_ptr->queue_limit[TIPC_HIGH_IMPORTANCE + 4] = 900;
	l_ptr->queue_limit[TIPC_CRITICAL_IMPORTANCE + 4] = 1200;
	l_ptr->queue_limit[CONN_MANAGER] = 1200;
	l_ptr->queue_limit[ROUTE_DISTRIBUTOR] = 1200;
	l_ptr->queue_limit[CHANGEOVER_PROTOCOL] = 2500;
	l_ptr->queue_limit[NAME_DISTRIBUTOR] = 3000;
	/* FRAGMENT and LAST_FRAGMENT packets */
	l_ptr->queue_limit[MSG_FRAGMENTER] = 4000;
}