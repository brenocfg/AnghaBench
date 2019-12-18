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
typedef  int /*<<< orphan*/  u8_t ;
typedef  void* u32_t ;
struct uip_tcp_pcb {int rto; int sv; int cwnd; scalar_t__ keepcnt; int /*<<< orphan*/  keepalive; int /*<<< orphan*/  recv; scalar_t__ polltmr; int /*<<< orphan*/  tmr; void* snd_lbb; void* lastack; void* snd_max; void* snd_nxt; void* snd_wl2; scalar_t__ rtime; scalar_t__ sa; int /*<<< orphan*/  mss; int /*<<< orphan*/  ttl; scalar_t__ tos; int /*<<< orphan*/  rcv_wnd; scalar_t__ snd_queuelen; int /*<<< orphan*/  snd_buf; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_MEMSET (struct uip_tcp_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UIP_TCP_KEEPDEFAULT ; 
 int /*<<< orphan*/  UIP_TCP_MSS ; 
 int /*<<< orphan*/  UIP_TCP_PRIO_NORMAL ; 
 int UIP_TCP_SLOW_INTERVAL ; 
 int /*<<< orphan*/  UIP_TCP_SND_BUF ; 
 int /*<<< orphan*/  UIP_TCP_TTL ; 
 int /*<<< orphan*/  UIP_TCP_WND ; 
 struct uip_tcp_pcb* memb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_tcp_nullrecv ; 
 int /*<<< orphan*/  uip_tcp_pcbs ; 
 int /*<<< orphan*/  uip_tcp_ticks ; 
 void* uip_tcpiss_next () ; 

struct uip_tcp_pcb* uip_tcp_pcballoc(u8_t prio)
{
	u32_t iss;
	struct uip_tcp_pcb *pcb = NULL;

	pcb = memb_alloc(&uip_tcp_pcbs);
	if(pcb!=NULL) {
		UIP_MEMSET(pcb,0,sizeof(struct uip_tcp_pcb));
		pcb->prio = UIP_TCP_PRIO_NORMAL;
		pcb->snd_buf = UIP_TCP_SND_BUF;
		pcb->snd_queuelen = 0;
		pcb->rcv_wnd = UIP_TCP_WND;
		pcb->tos = 0;
		pcb->ttl = UIP_TCP_TTL;
		pcb->mss = UIP_TCP_MSS;
		pcb->rto = 3000/UIP_TCP_SLOW_INTERVAL;
		pcb->sa = 0;
		pcb->sv = 3000/UIP_TCP_SLOW_INTERVAL;
		pcb->rtime = 0;
		pcb->cwnd = 1;
		iss = uip_tcpiss_next();
		pcb->snd_wl2 = iss;
		pcb->snd_nxt = iss;
		pcb->snd_max = iss;
		pcb->lastack = iss;
		pcb->snd_lbb = iss;
		pcb->tmr = uip_tcp_ticks;
		pcb->polltmr = 0;

		pcb->recv = uip_tcp_nullrecv;

		pcb->keepalive = UIP_TCP_KEEPDEFAULT;
		pcb->keepcnt = 0;
	}
	return pcb;
}