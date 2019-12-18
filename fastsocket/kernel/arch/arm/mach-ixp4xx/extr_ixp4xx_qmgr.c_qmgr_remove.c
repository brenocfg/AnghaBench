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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_IXP4XX_QM1 ; 
 int /*<<< orphan*/  IRQ_IXP4XX_QM2 ; 
 int /*<<< orphan*/  IXP4XX_QMGR_BASE_PHYS ; 
 int /*<<< orphan*/  IXP4XX_QMGR_REGION_SIZE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmgr_regs ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qmgr_remove(void)
{
	free_irq(IRQ_IXP4XX_QM1, NULL);
	free_irq(IRQ_IXP4XX_QM2, NULL);
	synchronize_irq(IRQ_IXP4XX_QM1);
	synchronize_irq(IRQ_IXP4XX_QM2);
	iounmap(qmgr_regs);
	release_mem_region(IXP4XX_QMGR_BASE_PHYS, IXP4XX_QMGR_REGION_SIZE);
}