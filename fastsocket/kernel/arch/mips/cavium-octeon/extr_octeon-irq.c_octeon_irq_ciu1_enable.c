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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 unsigned int OCTEON_IRQ_WDOG0 ; 
 int cvmx_get_core_num () ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  octeon_irq_ciu1_rwlock ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_irq_ciu1_enable(unsigned int irq)
{
	int coreid = cvmx_get_core_num();
	unsigned long flags;
	uint64_t en1;
	int bit = irq - OCTEON_IRQ_WDOG0;	/* Bit 0-63 of EN1 */

	/*
	 * A read lock is used here to make sure only one core is ever
	 * updating the CIU enable bits at a time.  During an enable
	 * the cores don't interfere with each other.  During a disable
	 * the write lock stops any enables that might cause a
	 * problem.
	 */
	read_lock_irqsave(&octeon_irq_ciu1_rwlock, flags);
	en1 = cvmx_read_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1));
	en1 |= 1ull << bit;
	cvmx_write_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1), en1);
	cvmx_read_csr(CVMX_CIU_INTX_EN1(coreid * 2 + 1));
	read_unlock_irqrestore(&octeon_irq_ciu1_rwlock, flags);
}