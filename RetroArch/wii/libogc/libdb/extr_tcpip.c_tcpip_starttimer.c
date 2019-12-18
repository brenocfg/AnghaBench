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
struct tcpip_sock {scalar_t__ pcb; } ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 scalar_t__ gettime () ; 
 struct tcpip_sock* tcpip_getsocket (int /*<<< orphan*/ ) ; 
 scalar_t__ tcpip_time ; 
 scalar_t__ uip_tcp_active_pcbs ; 
 scalar_t__ uip_tcp_tw_pcbs ; 

void tcpip_starttimer(s32_t s)
{
	struct tcpip_sock *sock;

	sock = tcpip_getsocket(s);
	if(!sock) return;

	if(tcpip_time==0 && sock->pcb && (uip_tcp_active_pcbs || uip_tcp_tw_pcbs)) tcpip_time = gettime();
}