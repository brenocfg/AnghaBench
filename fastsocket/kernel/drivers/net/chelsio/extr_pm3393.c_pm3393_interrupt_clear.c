#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct cmac {TYPE_1__* adapter; } ;
struct TYPE_3__ {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_INT_CAUSE ; 
 scalar_t__ A_PL_CAUSE ; 
 int /*<<< orphan*/  ELMER0_GP_BIT1 ; 
 int /*<<< orphan*/  F_PL_INTR_EXT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_INDICATION ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_INTERRUPT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MASTER_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IDU_INTERRUPT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_CHANGE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4ODP_INTERRUPT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXOAM_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_INTERRUPT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXOAM_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_INTERRUPT ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XTEF_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  pmread (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  t1_tpi_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_tpi_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pm3393_interrupt_clear(struct cmac *cmac)
{
	u32 elmer;
	u32 pl_intr;
	u32 val32;

	/* PM3393 - Clearing HW interrupt blocks. Note, this assumes
	 *          bit WCIMODE=0 for a clear-on-read.
	 */
	pmread(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_INTERRUPT, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_RXXG_INTERRUPT, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_TXXG_INTERRUPT, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_INDICATION,
	       &val32);
	pmread(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_STATUS, &val32);
	pmread(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_CHANGE, &val32);

	/* PM3393 - Global interrupt status
	 */
	pmread(cmac, SUNI1x10GEXP_REG_MASTER_INTERRUPT_STATUS, &val32);

	/* ELMER - External chip interrupts.
	 */
	t1_tpi_read(cmac->adapter, A_ELMER0_INT_CAUSE, &elmer);
	elmer |= ELMER0_GP_BIT1;
	t1_tpi_write(cmac->adapter, A_ELMER0_INT_CAUSE, elmer);

	/* TERMINATOR - PL_INTERUPTS_EXT
	 */
	pl_intr = readl(cmac->adapter->regs + A_PL_CAUSE);
	pl_intr |= F_PL_INTR_EXT;
	writel(pl_intr, cmac->adapter->regs + A_PL_CAUSE);

	return 0;
}