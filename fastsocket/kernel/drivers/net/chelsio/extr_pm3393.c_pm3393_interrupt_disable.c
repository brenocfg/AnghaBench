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
struct cmac {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_INT_ENABLE ; 
 int /*<<< orphan*/  ELMER0_GP_BIT1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_CONFIG_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_CONFIG_3 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm3393_interrupt_disable(struct cmac *cmac)
{
	u32 elmer;

	/* PM3393 - Enabling HW interrupt blocks. */
	pmwrite(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_3, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_3, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK, 0);
	pmwrite(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE, 0);

	/* PM3393 - Global interrupt enable */
	pmwrite(cmac, SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE, 0);

	/* ELMER - External chip interrupts. */
	t1_tpi_read(cmac->adapter, A_ELMER0_INT_ENABLE, &elmer);
	elmer &= ~ELMER0_GP_BIT1;
	t1_tpi_write(cmac->adapter, A_ELMER0_INT_ENABLE, elmer);

	/* TERMINATOR - PL_INTERUPTS_EXT */
	/* DO NOT DISABLE TERMINATOR's EXTERNAL INTERRUPTS. ANOTHER CHIP
	 * COULD WANT THEM ENABLED. We disable PM3393 at the ELMER level.
	 */

	return 0;
}