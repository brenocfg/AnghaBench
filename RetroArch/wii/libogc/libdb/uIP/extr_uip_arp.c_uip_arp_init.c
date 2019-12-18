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
typedef  size_t s32_t ;
struct TYPE_2__ {scalar_t__ time; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_STATE_EMPTY ; 
 size_t UIP_ARPTAB_SIZE ; 
 TYPE_1__* arp_table ; 

void
uip_arp_init(void)
{
	s32_t i;
	for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
		arp_table[i].state = ARP_STATE_EMPTY;
		arp_table[i].time = 0;
	}
}