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
typedef  int u32 ;
struct spider_net_card {int dummy; } ;

/* Variables and functions */
 int SPIDER_NET_BURSTLMT_VALUE ; 
 int SPIDER_NET_ECMODE ; 
 int SPIDER_NET_ECMODE_VALUE ; 
 int SPIDER_NET_FRAMENUM_VALUE ; 
 int SPIDER_NET_GDTBSTA ; 
 int SPIDER_NET_GDTDMACCNTR ; 
 int /*<<< orphan*/  SPIDER_NET_GFAFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFBFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFCFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFDFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFREECNNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GFTRESTRT ; 
 int SPIDER_NET_GFXFRAMES_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_GIPSECINIT ; 
 int /*<<< orphan*/  SPIDER_NET_GMACAPAUSE ; 
 int /*<<< orphan*/  SPIDER_NET_GMACBSTLMT ; 
 int /*<<< orphan*/  SPIDER_NET_GMACINTEN ; 
 int SPIDER_NET_GMACLENLMT ; 
 int SPIDER_NET_GMACOPEMD ; 
 int /*<<< orphan*/  SPIDER_NET_GMACTXPAUSE ; 
 int SPIDER_NET_GMRUA0FIL15R ; 
 int SPIDER_NET_GMRUAFILnR ; 
 int /*<<< orphan*/  SPIDER_NET_GMRWOLCTRL ; 
 int /*<<< orphan*/  SPIDER_NET_GONETIMENUM ; 
 int /*<<< orphan*/  SPIDER_NET_GREINTNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GRESUMINTNUM ; 
 int SPIDER_NET_GRXDMAEN ; 
 int /*<<< orphan*/  SPIDER_NET_GRXMDSET ; 
 int /*<<< orphan*/  SPIDER_NET_GTESTMD ; 
 int /*<<< orphan*/  SPIDER_NET_GTOUTFRMNUM ; 
 int /*<<< orphan*/  SPIDER_NET_GTTQMSK ; 
 int /*<<< orphan*/  SPIDER_NET_GTXMDSET ; 
 int SPIDER_NET_IPSECINIT_VALUE ; 
 int SPIDER_NET_LENLMT_VALUE ; 
 int SPIDER_NET_MACAPAUSE_VALUE ; 
 int SPIDER_NET_OPMODE_VALUE ; 
 int SPIDER_NET_RESTART_VALUE ; 
 int SPIDER_NET_RXMODE_VALUE ; 
 int SPIDER_NET_TXMODE_VALUE ; 
 int SPIDER_NET_TXPAUSE_VALUE ; 
 int SPIDER_NET_WOL_VALUE ; 
 int /*<<< orphan*/  spider_net_enable_rxchtails (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_enable_rxdmac (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int,int) ; 

__attribute__((used)) static void
spider_net_enable_card(struct spider_net_card *card)
{
	int i;
	/* the following array consists of (register),(value) pairs
	 * that are set in this function. A register of 0 ends the list */
	u32 regs[][2] = {
		{ SPIDER_NET_GRESUMINTNUM, 0 },
		{ SPIDER_NET_GREINTNUM, 0 },

		/* set interrupt frame number registers */
		/* clear the single DMA engine registers first */
		{ SPIDER_NET_GFAFRMNUM, SPIDER_NET_GFXFRAMES_VALUE },
		{ SPIDER_NET_GFBFRMNUM, SPIDER_NET_GFXFRAMES_VALUE },
		{ SPIDER_NET_GFCFRMNUM, SPIDER_NET_GFXFRAMES_VALUE },
		{ SPIDER_NET_GFDFRMNUM, SPIDER_NET_GFXFRAMES_VALUE },
		/* then set, what we really need */
		{ SPIDER_NET_GFFRMNUM, SPIDER_NET_FRAMENUM_VALUE },

		/* timer counter registers and stuff */
		{ SPIDER_NET_GFREECNNUM, 0 },
		{ SPIDER_NET_GONETIMENUM, 0 },
		{ SPIDER_NET_GTOUTFRMNUM, 0 },

		/* RX mode setting */
		{ SPIDER_NET_GRXMDSET, SPIDER_NET_RXMODE_VALUE },
		/* TX mode setting */
		{ SPIDER_NET_GTXMDSET, SPIDER_NET_TXMODE_VALUE },
		/* IPSEC mode setting */
		{ SPIDER_NET_GIPSECINIT, SPIDER_NET_IPSECINIT_VALUE },

		{ SPIDER_NET_GFTRESTRT, SPIDER_NET_RESTART_VALUE },

		{ SPIDER_NET_GMRWOLCTRL, 0 },
		{ SPIDER_NET_GTESTMD, 0x10000000 },
		{ SPIDER_NET_GTTQMSK, 0x00400040 },

		{ SPIDER_NET_GMACINTEN, 0 },

		/* flow control stuff */
		{ SPIDER_NET_GMACAPAUSE, SPIDER_NET_MACAPAUSE_VALUE },
		{ SPIDER_NET_GMACTXPAUSE, SPIDER_NET_TXPAUSE_VALUE },

		{ SPIDER_NET_GMACBSTLMT, SPIDER_NET_BURSTLMT_VALUE },
		{ 0, 0}
	};

	i = 0;
	while (regs[i][0]) {
		spider_net_write_reg(card, regs[i][0], regs[i][1]);
		i++;
	}

	/* clear unicast filter table entries 1 to 14 */
	for (i = 1; i <= 14; i++) {
		spider_net_write_reg(card,
				     SPIDER_NET_GMRUAFILnR + i * 8,
				     0x00080000);
		spider_net_write_reg(card,
				     SPIDER_NET_GMRUAFILnR + i * 8 + 4,
				     0x00000000);
	}

	spider_net_write_reg(card, SPIDER_NET_GMRUA0FIL15R, 0x08080000);

	spider_net_write_reg(card, SPIDER_NET_ECMODE, SPIDER_NET_ECMODE_VALUE);

	/* set chain tail adress for RX chains and
	 * enable DMA */
	spider_net_enable_rxchtails(card);
	spider_net_enable_rxdmac(card);

	spider_net_write_reg(card, SPIDER_NET_GRXDMAEN, SPIDER_NET_WOL_VALUE);

	spider_net_write_reg(card, SPIDER_NET_GMACLENLMT,
			     SPIDER_NET_LENLMT_VALUE);
	spider_net_write_reg(card, SPIDER_NET_GMACOPEMD,
			     SPIDER_NET_OPMODE_VALUE);

	spider_net_write_reg(card, SPIDER_NET_GDTDMACCNTR,
			     SPIDER_NET_GDTBSTA);
}