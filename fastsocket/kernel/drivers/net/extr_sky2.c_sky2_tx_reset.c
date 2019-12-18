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
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 long BMU_FIFO_RST ; 
 long BMU_RST_SET ; 
 int GMF_RST_SET ; 
 int /*<<< orphan*/  PREF_UNIT_CTRL ; 
 long PREF_UNIT_RST_SET ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 long RB_RST_SET ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXA_CTRL ; 
 int TXA_DIS_ALLOC ; 
 int TXA_DIS_FSYNC ; 
 int /*<<< orphan*/  TXA_ITI_INI ; 
 int /*<<< orphan*/  TXA_LIM_INI ; 
 int TXA_STOP_RC ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  Y2_QADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void sky2_tx_reset(struct sky2_hw *hw, unsigned port)
{
	/* Disable Force Sync bit and Enable Alloc bit */
	sky2_write8(hw, SK_REG(port, TXA_CTRL),
		    TXA_DIS_FSYNC | TXA_DIS_ALLOC | TXA_STOP_RC);

	/* Stop Interval Timer and Limit Counter of Tx Arbiter */
	sky2_write32(hw, SK_REG(port, TXA_ITI_INI), 0L);
	sky2_write32(hw, SK_REG(port, TXA_LIM_INI), 0L);

	/* Reset the PCI FIFO of the async Tx queue */
	sky2_write32(hw, Q_ADDR(txqaddr[port], Q_CSR),
		     BMU_RST_SET | BMU_FIFO_RST);

	/* Reset the Tx prefetch units */
	sky2_write32(hw, Y2_QADDR(txqaddr[port], PREF_UNIT_CTRL),
		     PREF_UNIT_RST_SET);

	sky2_write32(hw, RB_ADDR(txqaddr[port], RB_CTRL), RB_RST_SET);
	sky2_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_SET);
}