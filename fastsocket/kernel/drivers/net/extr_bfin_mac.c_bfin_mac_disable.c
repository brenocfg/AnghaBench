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
 unsigned int RE ; 
 unsigned int TE ; 
 unsigned int bfin_read_EMAC_OPMODE () ; 
 int /*<<< orphan*/  bfin_write_EMAC_OPMODE (unsigned int) ; 

__attribute__((used)) static void bfin_mac_disable(void)
{
	unsigned int opmode;

	opmode = bfin_read_EMAC_OPMODE();
	opmode &= (~RE);
	opmode &= (~TE);
	/* Turn off the EMAC */
	bfin_write_EMAC_OPMODE(opmode);
}