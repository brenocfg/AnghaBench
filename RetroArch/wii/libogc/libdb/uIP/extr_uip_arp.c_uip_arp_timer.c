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
typedef  size_t u8_t ;
struct TYPE_2__ {scalar_t__ time; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ ARP_MAXAGE ; 
 scalar_t__ ARP_MAXPENDING ; 
 scalar_t__ ARP_STATE_EMPTY ; 
 scalar_t__ ARP_STATE_EXPIRED ; 
 scalar_t__ ARP_STATE_PENDING ; 
 scalar_t__ ARP_STATE_STABLE ; 
 size_t UIP_ARPTAB_SIZE ; 
 TYPE_1__* arp_table ; 

void
uip_arp_timer(void)
{
	u8_t i;

	for(i=0;i<UIP_ARPTAB_SIZE;i++) {
		arp_table[i].time++;
		if(arp_table[i].state==ARP_STATE_STABLE && arp_table[i].time>=ARP_MAXAGE) {
			arp_table[i].state = ARP_STATE_EXPIRED;
		} else if(arp_table[i].state==ARP_STATE_PENDING) {
			if(arp_table[i].time>=ARP_MAXPENDING) arp_table[i].state = ARP_STATE_EXPIRED;
		}

		if(arp_table[i].state==ARP_STATE_EXPIRED) arp_table[i].state = ARP_STATE_EMPTY;
	}
}