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
struct uip_tcp_pcb {int dummy; } ;
struct tcpip_sock {int dummy; } ;
typedef  int s32_t ;

/* Variables and functions */
 int tcpip_allocsocket (struct uip_tcp_pcb*) ; 
 struct tcpip_sock* tcpip_getsocket (int) ; 
 int /*<<< orphan*/  uip_tcp_arg (struct uip_tcp_pcb*,struct tcpip_sock*) ; 
 int /*<<< orphan*/  uip_tcp_close (struct uip_tcp_pcb*) ; 
 struct uip_tcp_pcb* uip_tcp_new () ; 

s32_t tcpip_socket()
{
	s32_t s;
	struct tcpip_sock *sock;
	struct uip_tcp_pcb *pcb;

	pcb = uip_tcp_new();
	if(!pcb) return -1;

	s = tcpip_allocsocket(pcb);
	if(s<0) {
		uip_tcp_close(pcb);
		return -1;
	}

	sock = tcpip_getsocket(s);
	uip_tcp_arg(pcb,sock);

	return s;
}