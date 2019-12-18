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
struct tcpip_sock {int /*<<< orphan*/  pcb; } ;
typedef  size_t s32_t ;

/* Variables and functions */
 size_t UIP_TCPIP_SOCKS ; 
 struct tcpip_sock* tcpip_socks ; 

__attribute__((used)) static struct tcpip_sock* tcpip_getsocket(s32_t s)
{
	struct tcpip_sock *sock;

	if(s<0 || s>=UIP_TCPIP_SOCKS) return NULL;

	sock = &tcpip_socks[s];
	if(!sock->pcb) return NULL;

	return sock;
}