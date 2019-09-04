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
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ ) ; 
 struct utun_pcb* ifnet_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utun_free_pcb (struct utun_pcb*,int) ; 

__attribute__((used)) static void
utun_detached(ifnet_t interface)
{
	struct utun_pcb	*pcb = ifnet_softc(interface);
	(void)ifnet_release(interface);
	utun_free_pcb(pcb, true);
}