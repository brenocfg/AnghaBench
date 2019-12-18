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
struct uip_tcp_pcb {scalar_t__ state; int /*<<< orphan*/ * ooseq; int /*<<< orphan*/ * unacked; int /*<<< orphan*/ * unsent; } ;

/* Variables and functions */
 scalar_t__ UIP_CLOSED ; 
 scalar_t__ UIP_LISTEN ; 
 scalar_t__ UIP_TIME_WAIT ; 
 int /*<<< orphan*/  uip_tcpsegs_free (int /*<<< orphan*/ *) ; 

void uip_tcp_pcbpurge(struct uip_tcp_pcb *pcb)
{
	if(pcb->state!=UIP_CLOSED &&
		pcb->state!=UIP_TIME_WAIT &&
		pcb->state!=UIP_LISTEN) {
		uip_tcpsegs_free(pcb->ooseq);
		uip_tcpsegs_free(pcb->unsent);
		uip_tcpsegs_free(pcb->unacked);
		pcb->unsent = pcb->unacked = pcb->ooseq = NULL;
	}
}