#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct t1_rx_mode {int dummy; } ;
struct cmac {TYPE_1__* instance; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAC_DIRECTION_RX ; 
 int SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN ; 
 int SUNI1x10GEXP_BITMSK_RXXG_PMODE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_HIGH ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_LOW ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDHIGH ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDLOW ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm3393_disable (struct cmac*,int) ; 
 int /*<<< orphan*/  pm3393_enable (struct cmac*,int) ; 
 int /*<<< orphan*/  pmread (struct cmac*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * t1_get_next_mcaddr (struct t1_rx_mode*) ; 
 scalar_t__ t1_rx_mode_allmulti (struct t1_rx_mode*) ; 
 scalar_t__ t1_rx_mode_mc_cnt (struct t1_rx_mode*) ; 
 scalar_t__ t1_rx_mode_promisc (struct t1_rx_mode*) ; 

__attribute__((used)) static int pm3393_set_rx_mode(struct cmac *cmac, struct t1_rx_mode *rm)
{
	int enabled = cmac->instance->enabled & MAC_DIRECTION_RX;
	u32 rx_mode;

	/* Disable MAC RX before reconfiguring it */
	if (enabled)
		pm3393_disable(cmac, MAC_DIRECTION_RX);

	pmread(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2, &rx_mode);
	rx_mode &= ~(SUNI1x10GEXP_BITMSK_RXXG_PMODE |
		     SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN);
	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2,
		(u16)rx_mode);

	if (t1_rx_mode_promisc(rm)) {
		/* Promiscuous mode. */
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_PMODE;
	}
	if (t1_rx_mode_allmulti(rm)) {
		/* Accept all multicast. */
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_LOW, 0xffff);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDLOW, 0xffff);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDHIGH, 0xffff);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_HIGH, 0xffff);
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN;
	} else if (t1_rx_mode_mc_cnt(rm)) {
		/* Accept one or more multicast(s). */
		u8 *addr;
		int bit;
		u16 mc_filter[4] = { 0, };

		while ((addr = t1_get_next_mcaddr(rm))) {
			bit = (ether_crc(ETH_ALEN, addr) >> 23) & 0x3f;	/* bit[23:28] */
			mc_filter[bit >> 4] |= 1 << (bit & 0xf);
		}
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_LOW, mc_filter[0]);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDLOW, mc_filter[1]);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDHIGH, mc_filter[2]);
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_HIGH, mc_filter[3]);
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN;
	}

	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2, (u16)rx_mode);

	if (enabled)
		pm3393_enable(cmac, MAC_DIRECTION_RX);

	return 0;
}