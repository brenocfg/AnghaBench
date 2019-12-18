#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* timer; void* eth1_mgm; void* eth1; void* ata; void* ata2; void* ata1; void* ata0; void* sser1; void* sser0; void* ser3; void* ser2; void* ser1; } ;
typedef  TYPE_1__ reg_pinmux_rw_hwprot ;
typedef  enum fixed_function { ____Placeholder_fixed_function } fixed_function ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 int /*<<< orphan*/  PORT_D ; 
 int /*<<< orphan*/  PORT_E ; 
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int crisv32_pinmux_dealloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  crisv32_pinmux_init () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pinmux ; 
#define  pinmux_ata 139 
#define  pinmux_ata0 138 
#define  pinmux_ata1 137 
#define  pinmux_ata2 136 
#define  pinmux_ata3 135 
#define  pinmux_eth1 134 
 int /*<<< orphan*/  pinmux_lock ; 
#define  pinmux_ser1 133 
#define  pinmux_ser2 132 
#define  pinmux_ser3 131 
#define  pinmux_sser0 130 
#define  pinmux_sser1 129 
#define  pinmux_timer 128 
 char* pins ; 
 int /*<<< orphan*/  regi_pinmux ; 
 void* regk_pinmux_no ; 
 int /*<<< orphan*/  rw_hwprot ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int crisv32_pinmux_dealloc_fixed(enum fixed_function function)
{
	int ret = -EINVAL;
	char saved[sizeof pins];
	unsigned long flags;

	spin_lock_irqsave(&pinmux_lock, flags);

	/* Save internal data for recovery */
	memcpy(saved, pins, sizeof pins);

	crisv32_pinmux_init();	/* Must be done before we read rw_hwprot */

	reg_pinmux_rw_hwprot hwprot = REG_RD(pinmux, regi_pinmux, rw_hwprot);

	switch (function) {
	case pinmux_ser1:
		ret = crisv32_pinmux_dealloc(PORT_C, 4, 7);
		hwprot.ser1 = regk_pinmux_no;
		break;
	case pinmux_ser2:
		ret = crisv32_pinmux_dealloc(PORT_C, 8, 11);
		hwprot.ser2 = regk_pinmux_no;
		break;
	case pinmux_ser3:
		ret = crisv32_pinmux_dealloc(PORT_C, 12, 15);
		hwprot.ser3 = regk_pinmux_no;
		break;
	case pinmux_sser0:
		ret = crisv32_pinmux_dealloc(PORT_C, 0, 3);
		ret |= crisv32_pinmux_dealloc(PORT_C, 16, 16);
		hwprot.sser0 = regk_pinmux_no;
		break;
	case pinmux_sser1:
		ret = crisv32_pinmux_dealloc(PORT_D, 0, 4);
		hwprot.sser1 = regk_pinmux_no;
		break;
	case pinmux_ata0:
		ret = crisv32_pinmux_dealloc(PORT_D, 5, 7);
		ret |= crisv32_pinmux_dealloc(PORT_D, 15, 17);
		hwprot.ata0 = regk_pinmux_no;
		break;
	case pinmux_ata1:
		ret = crisv32_pinmux_dealloc(PORT_D, 0, 4);
		ret |= crisv32_pinmux_dealloc(PORT_E, 17, 17);
		hwprot.ata1 = regk_pinmux_no;
		break;
	case pinmux_ata2:
		ret = crisv32_pinmux_dealloc(PORT_C, 11, 15);
		ret |= crisv32_pinmux_dealloc(PORT_E, 3, 3);
		hwprot.ata2 = regk_pinmux_no;
		break;
	case pinmux_ata3:
		ret = crisv32_pinmux_dealloc(PORT_C, 8, 10);
		ret |= crisv32_pinmux_dealloc(PORT_C, 0, 2);
		hwprot.ata2 = regk_pinmux_no;
		break;
	case pinmux_ata:
		ret = crisv32_pinmux_dealloc(PORT_B, 0, 15);
		ret |= crisv32_pinmux_dealloc(PORT_D, 8, 15);
		hwprot.ata = regk_pinmux_no;
		break;
	case pinmux_eth1:
		ret = crisv32_pinmux_dealloc(PORT_E, 0, 17);
		hwprot.eth1 = regk_pinmux_no;
		hwprot.eth1_mgm = regk_pinmux_no;
		break;
	case pinmux_timer:
		ret = crisv32_pinmux_dealloc(PORT_C, 16, 16);
		hwprot.timer = regk_pinmux_no;
		spin_unlock_irqrestore(&pinmux_lock, flags);
		return ret;
	}

	if (!ret)
		REG_WR(pinmux, regi_pinmux, rw_hwprot, hwprot);
	else
		memcpy(pins, saved, sizeof pins);

	spin_unlock_irqrestore(&pinmux_lock, flags);

	return ret;
}