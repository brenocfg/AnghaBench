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
struct llc_station_state_ev {scalar_t__ type; scalar_t__ prim; scalar_t__ prim_type; } ;

/* Variables and functions */
 scalar_t__ LLC_DISABLE_PRIM ; 
 scalar_t__ LLC_PRIM_TYPE_REQ ; 
 scalar_t__ LLC_STATION_EV_TYPE_PRIM ; 
 struct llc_station_state_ev* llc_station_ev (struct sk_buff*) ; 

__attribute__((used)) static int llc_stat_ev_disable_req(struct sk_buff *skb)
{
	struct llc_station_state_ev *ev = llc_station_ev(skb);

	return ev->type == LLC_STATION_EV_TYPE_PRIM &&
	       ev->prim == LLC_DISABLE_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
}