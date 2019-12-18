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
typedef  scalar_t__ u32_t ;
struct uip_tcpseg {scalar_t__ len; struct uip_tcpseg* next; TYPE_1__* tcphdr; } ;
struct uip_tcp_pcb {int flags; scalar_t__ lastack; scalar_t__ snd_nxt; scalar_t__ rcv_nxt; scalar_t__ state; scalar_t__ snd_max; struct uip_tcpseg* unsent; struct uip_tcpseg* unacked; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; int /*<<< orphan*/  cwnd; int /*<<< orphan*/  snd_wnd; } ;
struct uip_tcp_hdr {int /*<<< orphan*/  chksum; scalar_t__ urgp; void* wnd; void* ackno; void* seqno; void* dst; void* src; } ;
struct uip_pbuf {int /*<<< orphan*/  tot_len; struct uip_tcp_hdr* payload; } ;
typedef  int /*<<< orphan*/  s8_t ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int /*<<< orphan*/  UIP_ERR_BUF ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 scalar_t__ UIP_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIP_PBUF_IP ; 
 int /*<<< orphan*/  UIP_PBUF_RAM ; 
 int /*<<< orphan*/  UIP_PROTO_TCP ; 
 scalar_t__ UIP_SYN_SENT ; 
 int /*<<< orphan*/  UIP_TCPH_FLAGS_SET (struct uip_tcp_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIP_TCPH_HDRLEN_SET (struct uip_tcp_hdr*,int) ; 
 int /*<<< orphan*/  UIP_TCPH_SET_FLAG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIP_TCP_ACK ; 
 int /*<<< orphan*/  UIP_TCP_HLEN ; 
 scalar_t__ UIP_TCP_SEQ_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ UIP_TCP_TCPLEN (struct uip_tcpseg*) ; 
 int UIP_TF_ACK_DELAY ; 
 int UIP_TF_ACK_NOW ; 
 void* htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_chksum_pseudo (struct uip_pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_ipoutput (struct uip_pbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uip_pbuf* uip_pbuf_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 struct uip_tcp_pcb* uip_tcp_input_pcb ; 
 int /*<<< orphan*/  uip_tcpoutput_segments (struct uip_tcpseg*,struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_tcpseg_free (struct uip_tcpseg*) ; 

s8_t uip_tcpoutput(struct uip_tcp_pcb *pcb)
{
	u32_t wnd;
	struct uip_pbuf *p;
	struct uip_tcp_hdr *tcphdr;
	struct uip_tcpseg *seg,*useg;

	if(uip_tcp_input_pcb==pcb) return 0;

	wnd = UIP_MIN(pcb->snd_wnd,pcb->cwnd);
	seg = pcb->unsent;
	useg = pcb->unacked;
	if(useg!=NULL) {
		for(;useg->next!=NULL;useg=useg->next);
	}

	if(pcb->flags&UIP_TF_ACK_NOW &&
		(seg==NULL || ntohl(seg->tcphdr->seqno)-pcb->lastack+seg->len>wnd)) {
		//printf("uip_tcpout: ACK - seqno = %u, ackno = %u\n",pcb->snd_nxt,pcb->rcv_nxt);
		p = uip_pbuf_alloc(UIP_PBUF_IP,UIP_TCP_HLEN,UIP_PBUF_RAM);
		if(p==NULL) {
			UIP_ERROR("uip_tcpoutput: (ACK) could not allocate pbuf.");
			return UIP_ERR_BUF;
		}
		pcb->flags &= ~(UIP_TF_ACK_DELAY|UIP_TF_ACK_NOW);

		tcphdr = p->payload;
		tcphdr->src	= htons(pcb->local_port);
		tcphdr->dst = htons(pcb->remote_port);
		tcphdr->seqno = htonl(pcb->snd_nxt);
		tcphdr->ackno = htonl(pcb->rcv_nxt);
		UIP_TCPH_FLAGS_SET(tcphdr,UIP_TCP_ACK);
		tcphdr->wnd = htons(pcb->rcv_wnd);
		tcphdr->urgp = 0;
		UIP_TCPH_HDRLEN_SET(tcphdr,5);

		tcphdr->chksum = 0;
		tcphdr->chksum = uip_chksum_pseudo(p,&pcb->local_ip,&pcb->remote_ip,UIP_PROTO_TCP,p->tot_len);

		uip_ipoutput(p,&pcb->local_ip,&pcb->remote_ip,pcb->ttl,pcb->tos,UIP_PROTO_TCP);
		uip_pbuf_free(p);

		return UIP_ERR_OK;
	}

	while(seg!=NULL && ntohl(seg->tcphdr->seqno)-pcb->lastack+seg->len<=wnd) {
		pcb->unsent = seg->next;
		if(pcb->state!=UIP_SYN_SENT) {
			UIP_TCPH_SET_FLAG(seg->tcphdr,UIP_TCP_ACK);
			pcb->flags &= ~(UIP_TF_ACK_DELAY|UIP_TF_ACK_NOW);
		}

		uip_tcpoutput_segments(seg,pcb);

		pcb->snd_nxt = ntohl(seg->tcphdr->seqno)+UIP_TCP_TCPLEN(seg);
		if(UIP_TCP_SEQ_LT(pcb->snd_max,pcb->snd_nxt)) pcb->snd_max = pcb->snd_nxt;

		if(UIP_TCP_TCPLEN(seg)>0) {
			seg->next = NULL;
			if(pcb->unacked==NULL) {
				pcb->unacked = seg;
				useg = seg;
			} else {
				if(UIP_TCP_SEQ_LT(ntohl(seg->tcphdr->seqno),ntohl(useg->tcphdr->seqno))) {
					seg->next = pcb->unacked;
					pcb->unacked = seg;
				} else {
					useg->next = seg;
					useg = useg->next;
				}
			}
		} else
			uip_tcpseg_free(seg);

		seg = pcb->unsent;
	}
	return UIP_ERR_OK;
}