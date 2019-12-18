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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {int dummy; } ;
struct dm1105_dev {int boardnr; } ;
typedef  scalar_t__ fe_sec_voltage_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM05_LNB_13V ; 
 int /*<<< orphan*/  DM05_LNB_18V ; 
 int /*<<< orphan*/  DM05_LNB_MASK ; 
 int /*<<< orphan*/  DM05_LNB_OFF ; 
#define  DM1105_BOARD_AXESS_DM05 130 
#define  DM1105_BOARD_DVBWORLD_2002 129 
#define  DM1105_BOARD_DVBWORLD_2004 128 
 int /*<<< orphan*/  DM1105_GPIOCTR ; 
 int /*<<< orphan*/  DM1105_GPIOVAL ; 
 int /*<<< orphan*/  DM1105_LNB_13V ; 
 int /*<<< orphan*/  DM1105_LNB_18V ; 
 int /*<<< orphan*/  DM1105_LNB_MASK ; 
 int /*<<< orphan*/  DM1105_LNB_OFF ; 
 scalar_t__ SEC_VOLTAGE_13 ; 
 scalar_t__ SEC_VOLTAGE_18 ; 
 int /*<<< orphan*/  dm_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dm1105_dev* frontend_to_dm1105_dev (struct dvb_frontend*) ; 

__attribute__((used)) static int dm1105_set_voltage(struct dvb_frontend *fe, fe_sec_voltage_t voltage)
{
	struct dm1105_dev *dev = frontend_to_dm1105_dev(fe);
	u32 lnb_mask, lnb_13v, lnb_18v, lnb_off;

	switch (dev->boardnr) {
	case DM1105_BOARD_AXESS_DM05:
		lnb_mask = DM05_LNB_MASK;
		lnb_off = DM05_LNB_OFF;
		lnb_13v = DM05_LNB_13V;
		lnb_18v = DM05_LNB_18V;
		break;
	case DM1105_BOARD_DVBWORLD_2002:
	case DM1105_BOARD_DVBWORLD_2004:
	default:
		lnb_mask = DM1105_LNB_MASK;
		lnb_off = DM1105_LNB_OFF;
		lnb_13v = DM1105_LNB_13V;
		lnb_18v = DM1105_LNB_18V;
	}

	dm_writel(DM1105_GPIOCTR, lnb_mask);
	if (voltage == SEC_VOLTAGE_18)
		dm_writel(DM1105_GPIOVAL, lnb_18v);
	else if (voltage == SEC_VOLTAGE_13)
		dm_writel(DM1105_GPIOVAL, lnb_13v);
	else
		dm_writel(DM1105_GPIOVAL, lnb_off);

	return 0;
}