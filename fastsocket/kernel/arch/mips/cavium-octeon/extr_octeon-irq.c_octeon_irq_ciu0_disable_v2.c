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
typedef  unsigned long long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0_W1C (int) ; 
 unsigned int OCTEON_IRQ_WORKQ0 ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void octeon_irq_ciu0_disable_v2(unsigned int irq)
{
	int index = cvmx_get_core_num() * 2;
	u64 mask = 1ull << (irq - OCTEON_IRQ_WORKQ0);

	cvmx_write_csr(CVMX_CIU_INTX_EN0_W1C(index), mask);
}