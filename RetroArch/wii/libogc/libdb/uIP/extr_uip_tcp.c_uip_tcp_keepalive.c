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
struct uip_tcp_pcb {int /*<<< orphan*/  ttl; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  rcv_wnd; scalar_t__ rcv_nxt; scalar_t__ snd_nxt; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; } ;
struct uip_tcp_hdr {scalar_t__ chksum; scalar_t__ urgp; void* wnd; void* ackno; void* seqno; void* dst; void* src; } ;
struct uip_pbuf {int /*<<< orphan*/  tot_len; struct uip_tcp_hdr* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_PBUF_IP ; 
 int /*<<< orphan*/  UIP_PBUF_RAM ; 
 int /*<<< orphan*/  UIP_PROTO_TCP ; 
 int /*<<< orphan*/  UIP_TCPH_HDRLEN_SET (struct uip_tcp_hdr*,int) ; 
 int /*<<< orphan*/  UIP_TCP_HLEN ; 
 void* htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ uip_chksum_pseudo (struct uip_pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_ipoutput (struct uip_pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uip_pbuf* uip_pbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 

void uip_tcp_keepalive(struct uip_tcp_pcb *pcb)
{
	struct uip_pbuf *p;
	struct uip_tcp_hdr *tcphdr;

	p = uip_pbuf_alloc(UIP_PBUF_IP,UIP_TCP_HLEN,UIP_PBUF_RAM);
	if(p==NULL) return;

	tcphdr = p->payload;
	tcphdr->src = htons(pcb->local_port);
	tcphdr->dst = htons(pcb->remote_port);
	tcphdr->seqno = htonl(pcb->snd_nxt-1);
	tcphdr->ackno = htonl(pcb->rcv_nxt);
	tcphdr->wnd = htons(pcb->rcv_wnd);
	tcphdr->urgp = 0;
	UIP_TCPH_HDRLEN_SET(tcphdr,5);

	tcphdr->chksum = 0;
	tcphdr->chksum = uip_chksum_pseudo(p,&pcb->local_ip,&pcb->remote_ip,UIP_PROTO_TCP,p->tot_len);

	uip_ipoutput(p,&pcb->local_ip,&pcb->remote_ip,pcb->ttl,0,UIP_PROTO_TCP);
	uip_pbuf_free(p);
}