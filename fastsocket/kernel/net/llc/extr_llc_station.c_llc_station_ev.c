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
struct sk_buff {scalar_t__ cb; } ;
struct llc_station_state_ev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static __inline__ struct llc_station_state_ev *
					llc_station_ev(struct sk_buff *skb)
{
	return (struct llc_station_state_ev *)skb->cb;
}