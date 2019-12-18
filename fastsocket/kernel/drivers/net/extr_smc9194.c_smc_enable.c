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

/* Variables and functions */
 scalar_t__ INT_MASK ; 
 scalar_t__ RCR ; 
 int /*<<< orphan*/  RCR_NORMAL ; 
 int /*<<< orphan*/  SMC_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 scalar_t__ TCR ; 
 int /*<<< orphan*/  TCR_NORMAL ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void smc_enable( int ioaddr )
{
	SMC_SELECT_BANK( 0 );
	/* see the header file for options in TCR/RCR NORMAL*/
	outw( TCR_NORMAL, ioaddr + TCR );
	outw( RCR_NORMAL, ioaddr + RCR );

	/* now, enable interrupts */
	SMC_SELECT_BANK( 2 );
	outb( SMC_INTERRUPT_MASK, ioaddr + INT_MASK );
}