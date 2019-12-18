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
typedef  int /*<<< orphan*/  FAS216_Info ;

/* Variables and functions */
 int CMD_NOP ; 
 int CMD_RESETCHIP ; 
 int CMD_WITHDMA ; 
 int CNTL2_ENF ; 
 int CNTL2_S2FE ; 
 int CNTL3_ADIDCHK ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_CNTL2 ; 
 int /*<<< orphan*/  REG_CNTL3 ; 
 int /*<<< orphan*/  REG_ID ; 
 int TYPE_Am53CF94 ; 
 int TYPE_EmFAS216 ; 
 int TYPE_NCR53C90 ; 
 int TYPE_NCR53C90A ; 
 int TYPE_NCR53C9x ; 
 int TYPE_QLFAS216 ; 
 int fas216_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fas216_detect_type(FAS216_Info *info)
{
	int family, rev;

	/*
	 * Reset the chip.
	 */
	fas216_writeb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_writeb(info, REG_CMD, CMD_NOP);

	/*
	 * Check to see if control reg 2 is present.
	 */
	fas216_writeb(info, REG_CNTL3, 0);
	fas216_writeb(info, REG_CNTL2, CNTL2_S2FE);

	/*
	 * If we are unable to read back control reg 2
	 * correctly, it is not present, and we have a
	 * NCR53C90.
	 */
	if ((fas216_readb(info, REG_CNTL2) & (~0xe0)) != CNTL2_S2FE)
		return TYPE_NCR53C90;

	/*
	 * Now, check control register 3
	 */
	fas216_writeb(info, REG_CNTL2, 0);
	fas216_writeb(info, REG_CNTL3, 0);
	fas216_writeb(info, REG_CNTL3, 5);

	/*
	 * If we are unable to read the register back
	 * correctly, we have a NCR53C90A
	 */
	if (fas216_readb(info, REG_CNTL3) != 5)
		return TYPE_NCR53C90A;

	/*
	 * Now read the ID from the chip.
	 */
	fas216_writeb(info, REG_CNTL3, 0);

	fas216_writeb(info, REG_CNTL3, CNTL3_ADIDCHK);
	fas216_writeb(info, REG_CNTL3, 0);

	fas216_writeb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_writeb(info, REG_CMD, CMD_WITHDMA | CMD_NOP);

	fas216_writeb(info, REG_CNTL2, CNTL2_ENF);
	fas216_writeb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_writeb(info, REG_CMD, CMD_NOP);

	rev     = fas216_readb(info, REG_ID);
	family  = rev >> 3;
	rev    &= 7;

	switch (family) {
	case 0x01:
		if (rev == 4)
			return TYPE_Am53CF94;
		break;

	case 0x02:
		switch (rev) {
		case 2:
			return TYPE_EmFAS216;
		case 3:
			return TYPE_QLFAS216;
		}
		break;

	default:
		break;
	}
	printk("family %x rev %x\n", family, rev);
	return TYPE_NCR53C9x;
}