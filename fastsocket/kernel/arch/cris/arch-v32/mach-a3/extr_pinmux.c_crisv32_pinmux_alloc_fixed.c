#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* i2c1_sda3; void* i2c1; void* i2c1_sda2; void* i2c1_sda1; void* i2c1_sen; void* i2c0; void* pwm2; void* pwm1; void* pwm0; void* pio; void* sser; void* sser_ser_dma6_7; void* ser4; void* ser3; void* ser2; void* ser1; void* vout_sync; void* vout; void* strdma0_2_video; void* tg_clk; void* tg; void* ccd_tg_200; void* ccd_tg_100; void* geth; void* eth_mdio; void* eth; void* dma0_1_eth; } ;
typedef  TYPE_1__ reg_pinmux_rw_hwprot ;
typedef  TYPE_1__ reg_clkgen_rw_clk_ctrl ;
typedef  enum fixed_function { ____Placeholder_fixed_function } fixed_function ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  clkgen ; 
 int crisv32_pinmux_alloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crisv32_pinmux_init () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pinmux ; 
#define  pinmux_eth 147 
 int /*<<< orphan*/  pinmux_fixed ; 
#define  pinmux_geth 146 
#define  pinmux_i2c0 145 
#define  pinmux_i2c1 144 
#define  pinmux_i2c1_3wire 143 
#define  pinmux_i2c1_sda1 142 
#define  pinmux_i2c1_sda2 141 
#define  pinmux_i2c1_sda3 140 
 int /*<<< orphan*/  pinmux_lock ; 
#define  pinmux_pio 139 
#define  pinmux_pwm0 138 
#define  pinmux_pwm1 137 
#define  pinmux_pwm2 136 
#define  pinmux_ser1 135 
#define  pinmux_ser2 134 
#define  pinmux_ser3 133 
#define  pinmux_ser4 132 
#define  pinmux_sser 131 
#define  pinmux_tg_ccd 130 
#define  pinmux_tg_cmos 129 
#define  pinmux_vout 128 
 char* pins ; 
 int /*<<< orphan*/  regi_clkgen ; 
 int /*<<< orphan*/  regi_pinmux ; 
 void* regk_clkgen_yes ; 
 void* regk_pinmux_yes ; 
 int /*<<< orphan*/  rw_clk_ctrl ; 
 int /*<<< orphan*/  rw_hwprot ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
crisv32_pinmux_alloc_fixed(enum fixed_function function)
{
	int ret = -EINVAL;
	char saved[sizeof pins];
	unsigned long flags;

	spin_lock_irqsave(&pinmux_lock, flags);

	/* Save internal data for recovery */
	memcpy(saved, pins, sizeof pins);

	crisv32_pinmux_init(); /* must be done before we read rw_hwprot */

	reg_pinmux_rw_hwprot hwprot = REG_RD(pinmux, regi_pinmux, rw_hwprot);
	reg_clkgen_rw_clk_ctrl clk_ctrl = REG_RD(clkgen, regi_clkgen,
		rw_clk_ctrl);

	switch (function) {
	case pinmux_eth:
		clk_ctrl.eth = regk_clkgen_yes;
		clk_ctrl.dma0_1_eth = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_B, 8, 23, pinmux_fixed);
		ret |= crisv32_pinmux_alloc(PORT_B, 24, 25, pinmux_fixed);
		hwprot.eth = hwprot.eth_mdio = regk_pinmux_yes;
		break;
	case pinmux_geth:
		ret = crisv32_pinmux_alloc(PORT_B, 0, 7, pinmux_fixed);
		hwprot.geth = regk_pinmux_yes;
		break;
	case pinmux_tg_cmos:
		clk_ctrl.ccd_tg_100 = clk_ctrl.ccd_tg_200 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_B, 27, 29, pinmux_fixed);
		hwprot.tg_clk = regk_pinmux_yes;
		break;
	case pinmux_tg_ccd:
		clk_ctrl.ccd_tg_100 = clk_ctrl.ccd_tg_200 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_B, 27, 31, pinmux_fixed);
		ret |= crisv32_pinmux_alloc(PORT_C, 0, 15, pinmux_fixed);
		hwprot.tg = hwprot.tg_clk = regk_pinmux_yes;
		break;
	case pinmux_vout:
		clk_ctrl.strdma0_2_video = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 8, 18, pinmux_fixed);
		hwprot.vout = hwprot.vout_sync = regk_pinmux_yes;
		break;
	case pinmux_ser1:
		clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 24, 25, pinmux_fixed);
		hwprot.ser1 = regk_pinmux_yes;
		break;
	case pinmux_ser2:
		clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 26, 27, pinmux_fixed);
		hwprot.ser2 = regk_pinmux_yes;
		break;
	case pinmux_ser3:
		clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 28, 29, pinmux_fixed);
		hwprot.ser3 = regk_pinmux_yes;
		break;
	case pinmux_ser4:
		clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 30, 31, pinmux_fixed);
		hwprot.ser4 = regk_pinmux_yes;
		break;
	case pinmux_sser:
		clk_ctrl.sser_ser_dma6_7 = regk_clkgen_yes;
		ret = crisv32_pinmux_alloc(PORT_A, 19, 23, pinmux_fixed);
		hwprot.sser = regk_pinmux_yes;
		break;
	case pinmux_pio:
		hwprot.pio = regk_pinmux_yes;
		ret = 0;
		break;
	case pinmux_pwm0:
		ret = crisv32_pinmux_alloc(PORT_A, 30, 30, pinmux_fixed);
		hwprot.pwm0 = regk_pinmux_yes;
		break;
	case pinmux_pwm1:
		ret = crisv32_pinmux_alloc(PORT_A, 31, 31, pinmux_fixed);
		hwprot.pwm1 = regk_pinmux_yes;
		break;
	case pinmux_pwm2:
		ret = crisv32_pinmux_alloc(PORT_B, 26, 26, pinmux_fixed);
		hwprot.pwm2 = regk_pinmux_yes;
		break;
	case pinmux_i2c0:
		ret = crisv32_pinmux_alloc(PORT_A, 0, 1, pinmux_fixed);
		hwprot.i2c0 = regk_pinmux_yes;
		break;
	case pinmux_i2c1:
		ret = crisv32_pinmux_alloc(PORT_A, 2, 3, pinmux_fixed);
		hwprot.i2c1 = regk_pinmux_yes;
		break;
	case pinmux_i2c1_3wire:
		ret = crisv32_pinmux_alloc(PORT_A, 2, 3, pinmux_fixed);
		ret |= crisv32_pinmux_alloc(PORT_A, 7, 7, pinmux_fixed);
		hwprot.i2c1 = hwprot.i2c1_sen = regk_pinmux_yes;
		break;
	case pinmux_i2c1_sda1:
		ret = crisv32_pinmux_alloc(PORT_A, 2, 4, pinmux_fixed);
		hwprot.i2c1 = hwprot.i2c1_sda1 = regk_pinmux_yes;
		break;
	case pinmux_i2c1_sda2:
		ret = crisv32_pinmux_alloc(PORT_A, 2, 3, pinmux_fixed);
		ret |= crisv32_pinmux_alloc(PORT_A, 5, 5, pinmux_fixed);
		hwprot.i2c1 = hwprot.i2c1_sda2 = regk_pinmux_yes;
		break;
	case pinmux_i2c1_sda3:
		ret = crisv32_pinmux_alloc(PORT_A, 2, 3, pinmux_fixed);
		ret |= crisv32_pinmux_alloc(PORT_A, 6, 6, pinmux_fixed);
		hwprot.i2c1 = hwprot.i2c1_sda3 = regk_pinmux_yes;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (!ret) {
		REG_WR(pinmux, regi_pinmux, rw_hwprot, hwprot);
		REG_WR(clkgen, regi_clkgen, rw_clk_ctrl, clk_ctrl);
	} else
		memcpy(pins, saved, sizeof pins);

  spin_unlock_irqrestore(&pinmux_lock, flags);

  return ret;
}