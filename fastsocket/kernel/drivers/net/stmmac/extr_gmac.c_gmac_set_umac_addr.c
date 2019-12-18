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
 int /*<<< orphan*/  GMAC_ADDR_HIGH (unsigned int) ; 
 int /*<<< orphan*/  GMAC_ADDR_LOW (unsigned int) ; 
 int /*<<< orphan*/  stmmac_set_mac_addr (unsigned long,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmac_set_umac_addr(unsigned long ioaddr, unsigned char *addr,
				unsigned int reg_n)
{
	stmmac_set_mac_addr(ioaddr, addr, GMAC_ADDR_HIGH(reg_n),
				GMAC_ADDR_LOW(reg_n));
}