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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int ctrlreg_value; int /*<<< orphan*/ * port_array; scalar_t__ lcr_base; int /*<<< orphan*/  misc_ctrl_value; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIT3 ; 
 int /*<<< orphan*/  BIT30 ; 
 int /*<<< orphan*/  BIT4 ; 
 int /*<<< orphan*/  BIT5 ; 
 int /*<<< orphan*/  lcr1_brdr_value ; 
 int /*<<< orphan*/  misc_ctrl_value ; 
 int read_ahead_count ; 
 int /*<<< orphan*/  sca_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_control_reg (TYPE_1__*) ; 

__attribute__((used)) static bool init_adapter(SLMP_INFO *info)
{
	int i;

	/* Set BIT30 of Local Control Reg 0x50 to reset SCA */
	volatile u32 *MiscCtrl = (u32 *)(info->lcr_base + 0x50);
	u32 readval;

	info->misc_ctrl_value |= BIT30;
	*MiscCtrl = info->misc_ctrl_value;

	/*
	 * Force at least 170ns delay before clearing
	 * reset bit. Each read from LCR takes at least
	 * 30ns so 10 times for 300ns to be safe.
	 */
	for(i=0;i<10;i++)
		readval = *MiscCtrl;

	info->misc_ctrl_value &= ~BIT30;
	*MiscCtrl = info->misc_ctrl_value;

	/* init control reg (all DTRs off, all clksel=input) */
	info->ctrlreg_value = 0xaa;
	write_control_reg(info);

	{
		volatile u32 *LCR1BRDR = (u32 *)(info->lcr_base + 0x2c);
		lcr1_brdr_value &= ~(BIT5 + BIT4 + BIT3);

		switch(read_ahead_count)
		{
		case 16:
			lcr1_brdr_value |= BIT5 + BIT4 + BIT3;
			break;
		case 8:
			lcr1_brdr_value |= BIT5 + BIT4;
			break;
		case 4:
			lcr1_brdr_value |= BIT5 + BIT3;
			break;
		case 0:
			lcr1_brdr_value |= BIT5;
			break;
		}

		*LCR1BRDR = lcr1_brdr_value;
		*MiscCtrl = misc_ctrl_value;
	}

	sca_init(info->port_array[0]);
	sca_init(info->port_array[2]);

	return true;
}