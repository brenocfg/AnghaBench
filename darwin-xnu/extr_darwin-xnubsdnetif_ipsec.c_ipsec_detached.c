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
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ ) ; 
 struct ipsec_pcb* ifnet_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_free_pcb (struct ipsec_pcb*,int) ; 

__attribute__((used)) static void
ipsec_detached(ifnet_t interface)
{
	struct ipsec_pcb *pcb = ifnet_softc(interface);
	(void)ifnet_release(interface);
	ipsec_free_pcb(pcb, true);
}