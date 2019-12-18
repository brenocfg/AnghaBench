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
struct uip_tcp_pcb {int dummy; } ;
struct tcpip_sock {struct tcpip_sock* next; TYPE_1__* pcb; } ;
typedef  int /*<<< orphan*/  s8_t ;
typedef  scalar_t__ s32_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_ABRT ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
 int /*<<< orphan*/  UIP_TF_NODELAY ; 
 struct tcpip_sock* tcpip_accepted_sockets ; 
 scalar_t__ tcpip_allocsocket (struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  tcpip_err ; 
 struct tcpip_sock* tcpip_getsocket (scalar_t__) ; 
 int /*<<< orphan*/  tcpip_poll ; 
 int /*<<< orphan*/  tcpip_recved ; 
 int /*<<< orphan*/  tcpip_sent ; 
 int /*<<< orphan*/  uip_tcp_arg (struct uip_tcp_pcb*,struct tcpip_sock*) ; 
 int /*<<< orphan*/  uip_tcp_close (struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_tcp_err (struct uip_tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcp_poll (struct uip_tcp_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uip_tcp_recv (struct uip_tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcp_sent (struct uip_tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s8_t tcpip_accept_func(void *arg,struct uip_tcp_pcb *newpcb,s8_t err)
{
	s32_t s;
	struct tcpip_sock *ptr,*newsock = NULL;
	struct tcpip_sock *sock = (struct tcpip_sock*)arg;

	UIP_LOG("tcpip_accept_func()");
	if(!sock) return UIP_ERR_ABRT;

	s = tcpip_allocsocket(newpcb);
	if(s<0) {
		uip_tcp_close(newpcb);
		return UIP_ERR_ABRT;
	}

	newsock = tcpip_getsocket(s);
	newsock->pcb->flags |= UIP_TF_NODELAY;

	ptr = tcpip_accepted_sockets;
	while(ptr && ptr->next) ptr = ptr->next;
	if(!ptr) tcpip_accepted_sockets = newsock;
	else ptr->next = newsock;

	uip_tcp_arg(newpcb,newsock);
	uip_tcp_recv(newpcb,tcpip_recved);
	uip_tcp_sent(newpcb,tcpip_sent);
	uip_tcp_err(newpcb,tcpip_err);
	uip_tcp_poll(newpcb,tcpip_poll,4);

	return UIP_ERR_OK;
}