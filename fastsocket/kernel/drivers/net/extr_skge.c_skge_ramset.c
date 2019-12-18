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
typedef  scalar_t__ u16 ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ Q_R1 ; 
 scalar_t__ Q_R2 ; 
 int /*<<< orphan*/  RB_ADDR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_ENA_OP_MD ; 
 int /*<<< orphan*/  RB_ENA_STFWD ; 
 int /*<<< orphan*/  RB_END ; 
 int /*<<< orphan*/  RB_RP ; 
 int /*<<< orphan*/  RB_RST_CLR ; 
 int /*<<< orphan*/  RB_RX_LTPP ; 
 int /*<<< orphan*/  RB_RX_UTPP ; 
 int /*<<< orphan*/  RB_START ; 
 int /*<<< orphan*/  RB_WP ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_ramset(struct skge_hw *hw, u16 q, u32 start, size_t len)
{
	u32 end;

	start /= 8;
	len /= 8;
	end = start + len - 1;

	skge_write8(hw, RB_ADDR(q, RB_CTRL), RB_RST_CLR);
	skge_write32(hw, RB_ADDR(q, RB_START), start);
	skge_write32(hw, RB_ADDR(q, RB_WP), start);
	skge_write32(hw, RB_ADDR(q, RB_RP), start);
	skge_write32(hw, RB_ADDR(q, RB_END), end);

	if (q == Q_R1 || q == Q_R2) {
		/* Set thresholds on receive queue's */
		skge_write32(hw, RB_ADDR(q, RB_RX_UTPP),
			     start + (2*len)/3);
		skge_write32(hw, RB_ADDR(q, RB_RX_LTPP),
			     start + (len/3));
	} else {
		/* Enable store & forward on Tx queue's because
		 * Tx FIFO is only 4K on Genesis and 1K on Yukon
		 */
		skge_write8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_STFWD);
	}

	skge_write8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_OP_MD);
}