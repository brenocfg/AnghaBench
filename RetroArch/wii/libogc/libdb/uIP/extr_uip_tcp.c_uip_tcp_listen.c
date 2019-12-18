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
struct uip_tcp_pcb_listen {int /*<<< orphan*/  accept; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  so_options; scalar_t__ state; int /*<<< orphan*/  local_port; int /*<<< orphan*/  cb_arg; } ;
struct uip_tcp_pcb {scalar_t__ state; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  so_options; int /*<<< orphan*/  local_port; int /*<<< orphan*/  cb_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_pcbs; } ;

/* Variables and functions */
 scalar_t__ UIP_LISTEN ; 
 int /*<<< orphan*/  UIP_SOF_ACCEPTCONN ; 
 int /*<<< orphan*/  UIP_TCP_REG (int /*<<< orphan*/ *,struct uip_tcp_pcb_listen*) ; 
 int /*<<< orphan*/  ip_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct uip_tcp_pcb_listen* memb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memb_free (int /*<<< orphan*/ *,struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_listen_tcp_pcbs ; 
 TYPE_1__ uip_tcp_listen_pcbs ; 
 int /*<<< orphan*/  uip_tcp_nullaccept ; 
 int /*<<< orphan*/  uip_tcp_pcbs ; 

struct uip_tcp_pcb* uip_tcp_listen(struct uip_tcp_pcb *pcb)
{
	struct uip_tcp_pcb_listen *lpcb;

	if(pcb->state==UIP_LISTEN) return pcb;

	lpcb = memb_alloc(&uip_listen_tcp_pcbs);
	if(lpcb==NULL) return NULL;

	lpcb->cb_arg = pcb->cb_arg;
	lpcb->local_port = pcb->local_port;
	lpcb->state = UIP_LISTEN;
	lpcb->so_options = pcb->so_options;
	lpcb->so_options |= UIP_SOF_ACCEPTCONN;
	lpcb->ttl = pcb->ttl;
	lpcb->tos = pcb->tos;
	ip_addr_set(&lpcb->local_ip,&pcb->local_ip);

	memb_free(&uip_tcp_pcbs,pcb);

	lpcb->accept = uip_tcp_nullaccept;

	UIP_TCP_REG(&uip_tcp_listen_pcbs.listen_pcbs,lpcb);
	return (struct uip_tcp_pcb*)lpcb;
}