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
struct idt77252_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAR_REG_CDC ; 
 int /*<<< orphan*/  SAR_REG_ICC ; 
 int /*<<< orphan*/  SAR_REG_VPEC ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idt77252_collect_stat(struct idt77252_dev *card)
{
	u32 cdc, vpec, icc;

	cdc = readl(SAR_REG_CDC);
	vpec = readl(SAR_REG_VPEC);
	icc = readl(SAR_REG_ICC);

#ifdef	NOTDEF
	printk("%s:", card->name);

	if (cdc & 0x7f0000) {
		char *s = "";

		printk(" [");
		if (cdc & (1 << 22)) {
			printk("%sRM ID", s);
			s = " | ";
		}
		if (cdc & (1 << 21)) {
			printk("%sCON TAB", s);
			s = " | ";
		}
		if (cdc & (1 << 20)) {
			printk("%sNO FB", s);
			s = " | ";
		}
		if (cdc & (1 << 19)) {
			printk("%sOAM CRC", s);
			s = " | ";
		}
		if (cdc & (1 << 18)) {
			printk("%sRM CRC", s);
			s = " | ";
		}
		if (cdc & (1 << 17)) {
			printk("%sRM FIFO", s);
			s = " | ";
		}
		if (cdc & (1 << 16)) {
			printk("%sRX FIFO", s);
			s = " | ";
		}
		printk("]");
	}

	printk(" CDC %04x, VPEC %04x, ICC: %04x\n",
	       cdc & 0xffff, vpec & 0xffff, icc & 0xffff);
#endif
}