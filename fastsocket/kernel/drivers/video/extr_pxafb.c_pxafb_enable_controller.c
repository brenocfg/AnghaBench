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
struct pxafb_info {int* fdadr; int reg_lccr0; int reg_lccr1; int reg_lccr2; int reg_lccr3; int lccr0; int reg_lccr4; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDADR0 ; 
 int /*<<< orphan*/  FDADR1 ; 
 int /*<<< orphan*/  LCCR0 ; 
 int LCCR0_ENB ; 
 int LCCR0_LCDT ; 
 int /*<<< orphan*/  LCCR1 ; 
 int /*<<< orphan*/  LCCR2 ; 
 int /*<<< orphan*/  LCCR3 ; 
 int /*<<< orphan*/  LCCR4 ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_writel (struct pxafb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void pxafb_enable_controller(struct pxafb_info *fbi)
{
	pr_debug("pxafb: Enabling LCD controller\n");
	pr_debug("fdadr0 0x%08x\n", (unsigned int) fbi->fdadr[0]);
	pr_debug("fdadr1 0x%08x\n", (unsigned int) fbi->fdadr[1]);
	pr_debug("reg_lccr0 0x%08x\n", (unsigned int) fbi->reg_lccr0);
	pr_debug("reg_lccr1 0x%08x\n", (unsigned int) fbi->reg_lccr1);
	pr_debug("reg_lccr2 0x%08x\n", (unsigned int) fbi->reg_lccr2);
	pr_debug("reg_lccr3 0x%08x\n", (unsigned int) fbi->reg_lccr3);

	/* enable LCD controller clock */
	clk_enable(fbi->clk);

	if (fbi->lccr0 & LCCR0_LCDT)
		return;

	/* Sequence from 11.7.10 */
	lcd_writel(fbi, LCCR4, fbi->reg_lccr4);
	lcd_writel(fbi, LCCR3, fbi->reg_lccr3);
	lcd_writel(fbi, LCCR2, fbi->reg_lccr2);
	lcd_writel(fbi, LCCR1, fbi->reg_lccr1);
	lcd_writel(fbi, LCCR0, fbi->reg_lccr0 & ~LCCR0_ENB);

	lcd_writel(fbi, FDADR0, fbi->fdadr[0]);
	lcd_writel(fbi, FDADR1, fbi->fdadr[1]);
	lcd_writel(fbi, LCCR0, fbi->reg_lccr0 | LCCR0_ENB);
}