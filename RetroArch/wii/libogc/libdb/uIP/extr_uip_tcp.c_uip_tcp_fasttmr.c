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
struct uip_tcp_pcb {int flags; struct uip_tcp_pcb* next; } ;

/* Variables and functions */
 int UIP_TF_ACK_DELAY ; 
 int UIP_TF_ACK_NOW ; 
 int /*<<< orphan*/  uip_tcp_acknow (struct uip_tcp_pcb*) ; 
 struct uip_tcp_pcb* uip_tcp_active_pcbs ; 

void uip_tcp_fasttmr()
{
	struct uip_tcp_pcb *pcb;

	for(pcb=uip_tcp_active_pcbs;pcb!=NULL;pcb=pcb->next) {
		if(pcb->flags&UIP_TF_ACK_DELAY) {
			uip_tcp_acknow(pcb);
			pcb->flags &= ~(UIP_TF_ACK_DELAY|UIP_TF_ACK_NOW);
		}
	}
}