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
typedef  size_t s32_t ;
struct TYPE_2__ {int sendevt; size_t socket; int /*<<< orphan*/  err; scalar_t__ flags; scalar_t__ recvevt; scalar_t__ lastoffset; int /*<<< orphan*/ * lastdata; struct uip_tcp_pcb* pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_OK ; 
 size_t UIP_TCPIP_SOCKS ; 
 TYPE_1__* tcpip_socks ; 

__attribute__((used)) static s32_t tcpip_allocsocket(struct uip_tcp_pcb *pcb)
{
	s32_t i;

	for(i=0;i<UIP_TCPIP_SOCKS;i++) {
		if(tcpip_socks[i].pcb==NULL) {
			tcpip_socks[i].pcb = pcb;
			tcpip_socks[i].lastdata = NULL;
			tcpip_socks[i].lastoffset = 0;
			tcpip_socks[i].recvevt = 0;
			tcpip_socks[i].sendevt = 1;
			tcpip_socks[i].flags = 0;
			tcpip_socks[i].socket = i;
			tcpip_socks[i].err = UIP_ERR_OK;
			return i;
		}
	}
	return -1;
}