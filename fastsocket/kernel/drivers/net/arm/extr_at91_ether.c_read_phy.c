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
 unsigned int AT91_EMAC_DATA ; 
 int /*<<< orphan*/  AT91_EMAC_MAN ; 
 unsigned char AT91_EMAC_MAN_802_3 ; 
 unsigned char AT91_EMAC_RW_R ; 
 unsigned int at91_emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_emac_write (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  at91_phy_wait () ; 

__attribute__((used)) static void read_phy(unsigned char phy_addr, unsigned char address, unsigned int *value)
{
	at91_emac_write(AT91_EMAC_MAN, AT91_EMAC_MAN_802_3 | AT91_EMAC_RW_R
		| ((phy_addr & 0x1f) << 23) | (address << 18));

	/* Wait until IDLE bit in Network Status register is cleared */
	at91_phy_wait();

	*value = at91_emac_read(AT91_EMAC_MAN) & AT91_EMAC_DATA;
}