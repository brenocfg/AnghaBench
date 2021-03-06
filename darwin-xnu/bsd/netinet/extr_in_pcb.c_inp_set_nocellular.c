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
struct inpcb {int /*<<< orphan*/  inp_route; int /*<<< orphan*/  inp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_NO_IFT_CELLULAR ; 
 int /*<<< orphan*/  ROUTE_RELEASE (int /*<<< orphan*/ *) ; 

void
inp_set_nocellular(struct inpcb *inp)
{
	inp->inp_flags |= INP_NO_IFT_CELLULAR;

	/* Blow away any cached route in the PCB */
	ROUTE_RELEASE(&inp->inp_route);
}