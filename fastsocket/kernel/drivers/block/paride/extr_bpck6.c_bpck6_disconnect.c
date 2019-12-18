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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  PPCSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc6_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc6_wr_extout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void bpck6_disconnect ( PIA *pi )
{
	if(verbose)
	{
		printk("disconnect\n");
	}
	ppc6_wr_extout(PPCSTRUCT(pi),0x0);
	ppc6_close(PPCSTRUCT(pi));
}