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
struct tcpip_sock {int /*<<< orphan*/ * pcb; } ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 struct tcpip_sock* tcpip_getsocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcp_close (int /*<<< orphan*/ *) ; 

void tcpip_close(s32_t s)
{
	struct tcpip_sock *sock;

	sock = tcpip_getsocket(s);
	if(sock==NULL) return;

	uip_tcp_close(sock->pcb);
	sock->pcb = NULL;
}