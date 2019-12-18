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
struct sk_buff {int dummy; } ;
struct llc_station_state_ev {scalar_t__ type; scalar_t__ prim_type; } ;

/* Variables and functions */
 scalar_t__ LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK ; 
 scalar_t__ LLC_STATION_EV_TYPE_SIMPLE ; 
 struct llc_station_state_ev* llc_station_ev (struct sk_buff*) ; 

__attribute__((used)) static int llc_stat_ev_enable_without_dup_addr_check(struct sk_buff *skb)
{
	struct llc_station_state_ev *ev = llc_station_ev(skb);

	return ev->type == LLC_STATION_EV_TYPE_SIMPLE &&
	       ev->prim_type ==
			LLC_STATION_EV_ENABLE_WITHOUT_DUP_ADDR_CHECK ? 0 : 1;
}