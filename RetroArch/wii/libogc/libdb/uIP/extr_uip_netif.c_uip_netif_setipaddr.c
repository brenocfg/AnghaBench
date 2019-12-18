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
struct uip_ip_addr {int dummy; } ;
struct uip_tcp_pcb_listen {struct uip_ip_addr local_ip; struct uip_tcp_pcb_listen* next; } ;
struct uip_tcp_pcb {struct uip_tcp_pcb* next; struct uip_ip_addr local_ip; } ;
struct uip_netif {struct uip_ip_addr ip_addr; } ;
struct TYPE_2__ {struct uip_tcp_pcb_listen* listen_pcbs; } ;

/* Variables and functions */
 scalar_t__ ip_addr_cmp (struct uip_ip_addr*,struct uip_ip_addr*) ; 
 int /*<<< orphan*/  ip_addr_set (struct uip_ip_addr*,struct uip_ip_addr*) ; 
 struct uip_tcp_pcb* uip_tcp_active_pcbs ; 
 TYPE_1__ uip_tcp_listen_pcbs ; 

void uip_netif_setipaddr(struct uip_netif *netif,struct uip_ip_addr *ipaddr)
{
#if UIP_TCP
	struct uip_tcp_pcb *pcb;
	struct uip_tcp_pcb_listen *lpcb;

	if((ip_addr_cmp(ipaddr,&netif->ip_addr))==0) {
		pcb = uip_tcp_active_pcbs;
		while(pcb!=NULL) {
			if(ip_addr_cmp(&pcb->local_ip,&netif->ip_addr)) {
				struct uip_tcp_pcb *next = pcb->next;
				pcb = next;
			} else {
				pcb = pcb->next;
			}
		}
		for(lpcb=uip_tcp_listen_pcbs.listen_pcbs;lpcb!=NULL;lpcb=lpcb->next) {
			if(ip_addr_cmp(&lpcb->local_ip,&netif->ip_addr)) {
				ip_addr_set(&lpcb->local_ip,ipaddr);
			}
		}
	}
#endif
	ip_addr_set(&netif->ip_addr,ipaddr);
}