#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8_t ;
typedef  scalar_t__ u32_t ;
typedef  scalar_t__ u16_t ;
struct uip_tcpseg {scalar_t__ len; TYPE_1__* tcphdr; struct uip_tcpseg* next; struct uip_pbuf* p; TYPE_1__* dataptr; } ;
struct uip_tcp_pcb {scalar_t__ snd_buf; scalar_t__ snd_lbb; scalar_t__ snd_queuelen; scalar_t__ mss; struct uip_tcpseg* unsent; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; } ;
struct uip_pbuf {TYPE_1__* payload; } ;
typedef  int /*<<< orphan*/  s8_t ;
struct TYPE_6__ {scalar_t__ urgp; int /*<<< orphan*/  seqno; void* dst; void* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int /*<<< orphan*/  UIP_ERR_MEM ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  UIP_MEMCPY (TYPE_1__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  UIP_PBUF_RAM ; 
 int /*<<< orphan*/  UIP_PBUF_ROM ; 
 int /*<<< orphan*/  UIP_PBUF_TRANSPORT ; 
 scalar_t__ UIP_TCPH_FLAGS (TYPE_1__*) ; 
 int /*<<< orphan*/  UIP_TCPH_FLAGS_SET (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  UIP_TCPH_HDRLEN_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UIP_TCPH_SET_FLAG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UIP_TCP_FIN ; 
 int /*<<< orphan*/  UIP_TCP_HLEN ; 
 int /*<<< orphan*/  UIP_TCP_PSH ; 
 scalar_t__ UIP_TCP_SND_QUEUELEN ; 
 scalar_t__ UIP_TCP_SYN ; 
 scalar_t__ UIP_TCP_TCPLEN (struct uip_tcpseg*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct uip_tcpseg* memb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memb_free (int /*<<< orphan*/ *,struct uip_tcpseg*) ; 
 void* uip_pbuf_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_pbuf_cat (struct uip_pbuf*,struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 scalar_t__ uip_pbuf_header (struct uip_pbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcp_segs ; 
 int /*<<< orphan*/  uip_tcpsegs_free (struct uip_tcpseg*) ; 

s8_t uip_tcpenqueue(struct uip_tcp_pcb *pcb,void *arg,u16_t len,u8_t flags,u8_t copy,u8_t *optdata,u8_t optlen)
{
	struct uip_pbuf *p;
	struct uip_tcpseg *seg,*useg,*queue = NULL;
	u32_t left,seqno;
	u16_t seglen;
	void *ptr;
	u8_t queue_len;

	if(len>pcb->snd_buf) {
		UIP_ERROR("uip_tcpenqueue: too much data (len>pcb->snd_buf).\n");
		return UIP_ERR_MEM;
	}

	left = len;
	ptr = arg;

	seqno = pcb->snd_lbb;
	queue_len = pcb->snd_queuelen;

	if(queue_len>=UIP_TCP_SND_QUEUELEN) {
		UIP_ERROR("uip_tcpenqueue: too long queue.");
		goto memerr;
	}
	useg = seg = queue = NULL;
	seglen = 0;
	while(queue==NULL || left>0) {
		seglen = left>pcb->mss?pcb->mss:len;
		seg = memb_alloc(&uip_tcp_segs);
		if(seg==NULL) {
			UIP_ERROR("uip_tcpenqueue: could not allocate memory for tcp_seg.");
			goto memerr;
		}

		seg->next = NULL;
		seg->p = NULL;

		if(queue==NULL) queue = seg;
		else useg->next = seg;

		useg = seg;

		if(optdata!=NULL) {
			if((seg->p=uip_pbuf_alloc(UIP_PBUF_TRANSPORT,optlen,UIP_PBUF_RAM))==NULL) {
				UIP_ERROR("uip_tcpenqueue: could not allocate memory for pbuf opdata.");
				goto memerr;
			}
			++queue_len;
			seg->dataptr = seg->p->payload;
		} else if(copy) {
			if((seg->p=uip_pbuf_alloc(UIP_PBUF_TRANSPORT,seglen,UIP_PBUF_RAM))==NULL) {
				UIP_ERROR("uip_tcpenqueue: could not allocate memory for pbuf copy size.");
				goto memerr;
			}

			++queue_len;
			if(ptr!=NULL) UIP_MEMCPY(seg->p->payload,ptr,seglen);

			seg->dataptr = seg->p->payload;
		} else {
			if((p=uip_pbuf_alloc(UIP_PBUF_TRANSPORT,seglen,UIP_PBUF_ROM))==NULL) {
				UIP_ERROR("uip_tcpenqueue: could not allocate memory for zero-copy pbuf.");
				goto memerr;
			}

			++queue_len;
			p->payload = ptr;
			seg->dataptr = ptr;
			if((seg->p=uip_pbuf_alloc(UIP_PBUF_TRANSPORT,0,UIP_PBUF_RAM))==NULL) {
				UIP_LOG("uip_tcpenqueue: could not allocate memory for header pbuf.");
				uip_pbuf_free(p);
				goto memerr;
			}

			++queue_len;
			uip_pbuf_cat(seg->p,p);
			p = NULL;
		}

		if(queue_len>UIP_TCP_SND_QUEUELEN) {
			UIP_ERROR("uip_tcpenqueue: queue too long.");
			goto memerr;
		}

		seg->len = seglen;
		if(uip_pbuf_header(seg->p,UIP_TCP_HLEN)) {
			UIP_ERROR("uip_tcpenqueue: no room for TCP header in pbuf.");
			goto memerr;
		}

		seg->tcphdr = seg->p->payload;
		seg->tcphdr->src = htons(pcb->local_port);
		seg->tcphdr->dst = htons(pcb->remote_port);
		seg->tcphdr->seqno = htonl(seqno);
		seg->tcphdr->urgp = 0;
		UIP_TCPH_FLAGS_SET(seg->tcphdr,flags);
		if(optdata==NULL) UIP_TCPH_HDRLEN_SET(seg->tcphdr,5);
		else {
			UIP_TCPH_HDRLEN_SET(seg->tcphdr,(5+(optlen/4)));
			UIP_MEMCPY(seg->dataptr,optdata,optlen);
		}
		left -= seglen;
		seqno += seglen;
		ptr = (void*)((u8_t*)ptr+seglen);
	}

	if(pcb->unsent==NULL) useg = NULL;
	else {
		for(useg=pcb->unsent;useg->next!=NULL;useg=useg->next);
	}

	if(useg!=NULL &&
		UIP_TCP_TCPLEN(useg)!=0 &&
		!(UIP_TCPH_FLAGS(useg->tcphdr)&(UIP_TCP_SYN|UIP_TCP_FIN)) &&
		!(flags&(UIP_TCP_SYN|UIP_TCP_FIN)) &&
		useg->len+queue->len<=pcb->mss) {

		uip_pbuf_header(queue->p,-UIP_TCP_HLEN);
		uip_pbuf_cat(useg->p,queue->p);

		useg->len += queue->len;
		useg->next = queue->next;
		if(seg==queue) seg = NULL;

		memb_free(&uip_tcp_segs,queue);
	} else {
		if(useg==NULL) pcb->unsent = queue;
		else useg->next = queue;
	}

	if(flags&UIP_TCP_SYN || flags&UIP_TCP_FIN) len++;

	pcb->snd_lbb += len;
	pcb->snd_buf -= len;
	pcb->snd_queuelen = queue_len;

	if(seg!=NULL && seglen>0 && seg->tcphdr!=NULL) UIP_TCPH_SET_FLAG(seg->tcphdr,UIP_TCP_PSH);

	return UIP_ERR_OK;
memerr:
	if(queue!=NULL) uip_tcpsegs_free(queue);
	return UIP_ERR_MEM;
}