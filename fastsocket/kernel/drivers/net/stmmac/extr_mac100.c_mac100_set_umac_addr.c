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
 int /*<<< orphan*/  MAC_ADDR_HIGH ; 
 int /*<<< orphan*/  MAC_ADDR_LOW ; 
 int /*<<< orphan*/  stmmac_set_mac_addr (unsigned long,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac100_set_umac_addr(unsigned long ioaddr, unsigned char *addr,
			  unsigned int reg_n)
{
	stmmac_set_mac_addr(ioaddr, addr, MAC_ADDR_HIGH, MAC_ADDR_LOW);
}