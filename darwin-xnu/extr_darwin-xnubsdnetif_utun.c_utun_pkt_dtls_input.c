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
struct utun_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */

int
utun_pkt_dtls_input(struct utun_pcb *pcb, mbuf_t *pkt, protocol_family_t family)
{
#pragma unused(pcb)
#pragma unused(pkt)
#pragma unused(family)
	return 0;
}