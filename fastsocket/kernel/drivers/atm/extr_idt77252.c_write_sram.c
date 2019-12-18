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
typedef  unsigned long u32 ;
struct idt77252_dev {int* tst; int tst_size; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned long SAR_CMD_WRITE_SRAM ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 int /*<<< orphan*/  SAR_REG_DR0 ; 
 scalar_t__ idt77252_sram_write_errors ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_sram(struct idt77252_dev *card, unsigned long addr, u32 value)
{
	unsigned long flags;

	if ((idt77252_sram_write_errors == 0) &&
	    (((addr > card->tst[0] + card->tst_size - 2) &&
	      (addr < card->tst[0] + card->tst_size)) ||
	     ((addr > card->tst[1] + card->tst_size - 2) &&
	      (addr < card->tst[1] + card->tst_size)))) {
		printk("%s: ERROR: TST JMP section at %08lx written: %08x\n",
		       card->name, addr, value);
	}

	spin_lock_irqsave(&card->cmd_lock, flags);
	writel(value, SAR_REG_DR0);
	writel(SAR_CMD_WRITE_SRAM | (addr << 2), SAR_REG_CMD);
	waitfor_idle(card);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
}