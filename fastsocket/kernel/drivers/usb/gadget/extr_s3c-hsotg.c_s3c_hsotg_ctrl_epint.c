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
struct s3c_hsotg {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C_DAINTMSK ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c_hsotg_ctrl_epint(struct s3c_hsotg *hsotg,
				 unsigned int ep, unsigned int dir_in,
				 unsigned int en)
{
	unsigned long flags;
	u32 bit = 1 << ep;
	u32 daint;

	if (!dir_in)
		bit <<= 16;

	local_irq_save(flags);
	daint = readl(hsotg->regs + S3C_DAINTMSK);
	if (en)
		daint |= bit;
	else
		daint &= ~bit;
	writel(daint, hsotg->regs + S3C_DAINTMSK);
	local_irq_restore(flags);
}