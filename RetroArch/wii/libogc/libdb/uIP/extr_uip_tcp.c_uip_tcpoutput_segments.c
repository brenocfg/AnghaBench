#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct uip_tcpseg {TYPE_2__* p; TYPE_1__* tcphdr; } ;
struct uip_tcp_pcb {scalar_t__ rcv_wnd; scalar_t__ mss; scalar_t__ rttest; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  rtseq; scalar_t__ rtime; int /*<<< orphan*/  rcv_nxt; } ;
struct uip_netif {int /*<<< orphan*/  ip_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  tot_len; TYPE_1__* payload; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {scalar_t__ chksum; int /*<<< orphan*/  seqno; scalar_t__ wnd; int /*<<< orphan*/  ackno; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int /*<<< orphan*/  UIP_PROTO_TCP ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (scalar_t__) ; 
 scalar_t__ ip_addr_isany (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ uip_chksum_pseudo (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_ipoutput (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uip_netif* uip_iproute (int /*<<< orphan*/ *) ; 
 scalar_t__ uip_tcp_ticks ; 

__attribute__((used)) static void uip_tcpoutput_segments(struct uip_tcpseg *seg,struct uip_tcp_pcb *pcb)
{
	u16_t len;
	struct uip_netif *netif;

	seg->tcphdr->ackno = htonl(pcb->rcv_nxt);
	if(pcb->rcv_wnd<pcb->mss) seg->tcphdr->wnd = 0;
	else seg->tcphdr->wnd = htons(pcb->rcv_wnd);

	if(ip_addr_isany(&pcb->local_ip)) {
		netif = uip_iproute(&pcb->remote_ip);
		if(netif==NULL) {
			UIP_ERROR("uip_tcpoutput_segments: no route found.");
			return;
		}
		ip_addr_set(&pcb->local_ip,&netif->ip_addr);
	}

	pcb->rtime = 0;
	if(pcb->rttest==0) {
		pcb->rttest = uip_tcp_ticks;
		pcb->rtseq = ntohl(seg->tcphdr->seqno);
	}

	len = (u16_t)((u8_t*)seg->tcphdr-(u8_t*)seg->p->payload);
	seg->p->len -= len;
	seg->p->tot_len -= len;
	seg->p->payload = seg->tcphdr;

	seg->tcphdr->chksum = 0;
	seg->tcphdr->chksum = uip_chksum_pseudo(seg->p,&pcb->local_ip,&pcb->remote_ip,UIP_PROTO_TCP,seg->p->tot_len);

	uip_ipoutput(seg->p,&pcb->local_ip,&pcb->remote_ip,pcb->ttl,pcb->tos,UIP_PROTO_TCP);
}