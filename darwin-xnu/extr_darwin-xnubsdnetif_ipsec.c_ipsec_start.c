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
struct ipsec_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ ifnet_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ipsec_pcb* ifnet_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ipsec_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipsec_start(ifnet_t	interface)
{
	mbuf_t data;
	struct ipsec_pcb *pcb = ifnet_softc(interface);

	VERIFY(pcb != NULL);
	for (;;) {
		if (ifnet_dequeue(interface, &data) != 0)
			break;
		if (ipsec_output(interface, data) != 0)
			break;
	}
}