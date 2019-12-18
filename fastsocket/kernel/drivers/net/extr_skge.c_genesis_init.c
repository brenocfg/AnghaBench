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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2_BSC_CTRL ; 
 int /*<<< orphan*/  B2_BSC_INI ; 
 int /*<<< orphan*/  B3_MA_RCINI_RX1 ; 
 int /*<<< orphan*/  B3_MA_RCINI_RX2 ; 
 int /*<<< orphan*/  B3_MA_RCINI_TX1 ; 
 int /*<<< orphan*/  B3_MA_RCINI_TX2 ; 
 int /*<<< orphan*/  B3_MA_TOINI_RX1 ; 
 int /*<<< orphan*/  B3_MA_TOINI_RX2 ; 
 int /*<<< orphan*/  B3_MA_TOINI_TX1 ; 
 int /*<<< orphan*/  B3_MA_TOINI_TX2 ; 
 int /*<<< orphan*/  B3_MA_TO_CTRL ; 
 int /*<<< orphan*/  B3_PA_CTRL ; 
 int /*<<< orphan*/  B3_PA_TOINI_RX1 ; 
 int /*<<< orphan*/  B3_PA_TOINI_RX2 ; 
 int /*<<< orphan*/  B3_PA_TOINI_TX1 ; 
 int /*<<< orphan*/  B3_PA_TOINI_TX2 ; 
 int /*<<< orphan*/  BSC_START ; 
 int /*<<< orphan*/  MA_RST_CLR ; 
 int /*<<< orphan*/  PA_RST_CLR ; 
 int SK_BLK_DUR ; 
 int SK_FACT_53 ; 
 int /*<<< orphan*/  SK_MAC_TO_53 ; 
 int /*<<< orphan*/  SK_PKT_TO_MAX ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genesis_init(struct skge_hw *hw)
{
	/* set blink source counter */
	skge_write32(hw, B2_BSC_INI, (SK_BLK_DUR * SK_FACT_53) / 100);
	skge_write8(hw, B2_BSC_CTRL, BSC_START);

	/* configure mac arbiter */
	skge_write16(hw, B3_MA_TO_CTRL, MA_RST_CLR);

	/* configure mac arbiter timeout values */
	skge_write8(hw, B3_MA_TOINI_RX1, SK_MAC_TO_53);
	skge_write8(hw, B3_MA_TOINI_RX2, SK_MAC_TO_53);
	skge_write8(hw, B3_MA_TOINI_TX1, SK_MAC_TO_53);
	skge_write8(hw, B3_MA_TOINI_TX2, SK_MAC_TO_53);

	skge_write8(hw, B3_MA_RCINI_RX1, 0);
	skge_write8(hw, B3_MA_RCINI_RX2, 0);
	skge_write8(hw, B3_MA_RCINI_TX1, 0);
	skge_write8(hw, B3_MA_RCINI_TX2, 0);

	/* configure packet arbiter timeout */
	skge_write16(hw, B3_PA_CTRL, PA_RST_CLR);
	skge_write16(hw, B3_PA_TOINI_RX1, SK_PKT_TO_MAX);
	skge_write16(hw, B3_PA_TOINI_TX1, SK_PKT_TO_MAX);
	skge_write16(hw, B3_PA_TOINI_RX2, SK_PKT_TO_MAX);
	skge_write16(hw, B3_PA_TOINI_TX2, SK_PKT_TO_MAX);
}