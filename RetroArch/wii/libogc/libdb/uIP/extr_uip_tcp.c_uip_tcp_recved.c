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
typedef  int u32_t ;
typedef  int u16_t ;
struct uip_tcp_pcb {int rcv_wnd; int flags; } ;

/* Variables and functions */
 int UIP_TCP_WND ; 
 int UIP_TF_ACK_DELAY ; 
 int UIP_TF_ACK_NOW ; 
 int /*<<< orphan*/  uip_tcp_ack (struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_tcp_acknow (struct uip_tcp_pcb*) ; 

void uip_tcp_recved(struct uip_tcp_pcb *pcb,u16_t len)
{
	if((u32_t)pcb->rcv_wnd+len>UIP_TCP_WND) pcb->rcv_wnd = UIP_TCP_WND;
	else pcb->rcv_wnd += len;

	if(!(pcb->flags&UIP_TF_ACK_DELAY) && !(pcb->flags&UIP_TF_ACK_NOW)) {
		uip_tcp_ack(pcb);
	} else if(pcb->flags&UIP_TF_ACK_DELAY && pcb->rcv_wnd>=UIP_TCP_WND/2) {
		uip_tcp_acknow(pcb);
	}
}