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
struct uip_tcpseg {TYPE_1__* tcphdr; struct uip_tcpseg* next; } ;
struct uip_tcp_pcb {int /*<<< orphan*/  nrtx; struct uip_tcpseg* unsent; int /*<<< orphan*/  snd_nxt; struct uip_tcpseg* unacked; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcpoutput (struct uip_tcp_pcb*) ; 

void uip_tcp_rexmit_rto(struct uip_tcp_pcb *pcb)
{
	struct uip_tcpseg *seg;

	if(pcb->unacked==NULL) return;

	for(seg=pcb->unacked;seg->next!=NULL;seg=seg->next);

	seg->next = pcb->unsent;
	pcb->unsent = pcb->unacked;
	pcb->unacked = NULL;

	pcb->snd_nxt = ntohl(pcb->unsent->tcphdr->seqno);
	pcb->nrtx++;

	uip_tcpoutput(pcb);
}