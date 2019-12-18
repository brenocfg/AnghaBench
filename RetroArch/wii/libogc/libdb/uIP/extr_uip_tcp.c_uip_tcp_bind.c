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
typedef  scalar_t__ u16_t ;
struct uip_ip_addr {int dummy; } ;
struct uip_tcp_pcb {scalar_t__ local_port; struct uip_ip_addr local_ip; struct uip_tcp_pcb* next; } ;
typedef  int /*<<< orphan*/  s8_t ;
struct TYPE_2__ {scalar_t__ pcbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_ERR_USE ; 
 scalar_t__ ip_addr_cmp (struct uip_ip_addr*,struct uip_ip_addr*) ; 
 scalar_t__ ip_addr_isany (struct uip_ip_addr*) ; 
 struct uip_tcp_pcb* uip_tcp_active_pcbs ; 
 TYPE_1__ uip_tcp_listen_pcbs ; 
 scalar_t__ uip_tcp_newport () ; 

s8_t uip_tcp_bind(struct uip_tcp_pcb *pcb,struct uip_ip_addr *ipaddr,u16_t port)
{
	struct uip_tcp_pcb *cpcb;

	if(port==0) port = uip_tcp_newport();

	for(cpcb=(struct uip_tcp_pcb*)uip_tcp_listen_pcbs.pcbs;cpcb!=NULL;cpcb=cpcb->next) {
		if(cpcb->local_port==port) {
			if(ip_addr_isany(&cpcb->local_ip) ||
				ip_addr_isany(ipaddr) ||
				ip_addr_cmp(&cpcb->local_ip,ipaddr)) return UIP_ERR_USE;
		}
	}

	for(cpcb=uip_tcp_active_pcbs;cpcb!=NULL;cpcb=cpcb->next) {
		if(cpcb->local_port==port) {
			if(ip_addr_isany(&cpcb->local_ip) ||
				ip_addr_isany(ipaddr) ||
				ip_addr_cmp(&cpcb->local_ip,ipaddr)) return UIP_ERR_USE;
		}
	}

	if(!ip_addr_isany(ipaddr)) pcb->local_ip = *ipaddr;
	pcb->local_port = port;

	return UIP_ERR_OK;
}