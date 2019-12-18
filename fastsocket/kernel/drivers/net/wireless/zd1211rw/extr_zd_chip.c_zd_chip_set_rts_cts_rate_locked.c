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
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_RTS_CTS_RATE ; 
 int RTSCTS_SH_CTS_MOD_TYPE ; 
 int RTSCTS_SH_CTS_PMB_TYPE ; 
 int RTSCTS_SH_CTS_RATE ; 
 int RTSCTS_SH_RTS_MOD_TYPE ; 
 int RTSCTS_SH_RTS_PMB_TYPE ; 
 int RTSCTS_SH_RTS_RATE ; 
 int /*<<< orphan*/  ZD_CCK_RATE_11M ; 
 int ZD_PURE_RATE (int /*<<< orphan*/ ) ; 
 int ZD_RX_CCK ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_iowrite32_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 

int zd_chip_set_rts_cts_rate_locked(struct zd_chip *chip,
				    int preamble)
{
	u32 value = 0;

	dev_dbg_f(zd_chip_dev(chip), "preamble=%x\n", preamble);
	value |= preamble << RTSCTS_SH_RTS_PMB_TYPE;
	value |= preamble << RTSCTS_SH_CTS_PMB_TYPE;

	/* We always send 11M RTS/self-CTS messages, like the vendor driver. */
	value |= ZD_PURE_RATE(ZD_CCK_RATE_11M) << RTSCTS_SH_RTS_RATE;
	value |= ZD_RX_CCK << RTSCTS_SH_RTS_MOD_TYPE;
	value |= ZD_PURE_RATE(ZD_CCK_RATE_11M) << RTSCTS_SH_CTS_RATE;
	value |= ZD_RX_CCK << RTSCTS_SH_CTS_MOD_TYPE;

	return zd_iowrite32_locked(chip, value, CR_RTS_CTS_RATE);
}