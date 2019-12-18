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

/* Variables and functions */
 int /*<<< orphan*/  EBI_CSR1 ; 
 int /*<<< orphan*/  EBI_LOCK ; 
 int INTEGRATOR_EBI_WRITE_ENABLE ; 
 int INTEGRATOR_SC_CTRL_nFLVPPEN ; 
 int INTEGRATOR_SC_CTRL_nFLWP ; 
 int /*<<< orphan*/  SC_CTRLC ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ap_flash_init(void)
{
	u32 tmp;

	writel(INTEGRATOR_SC_CTRL_nFLVPPEN | INTEGRATOR_SC_CTRL_nFLWP, SC_CTRLC);

	tmp = readl(EBI_CSR1) | INTEGRATOR_EBI_WRITE_ENABLE;
	writel(tmp, EBI_CSR1);

	if (!(readl(EBI_CSR1) & INTEGRATOR_EBI_WRITE_ENABLE)) {
		writel(0xa05f, EBI_LOCK);
		writel(tmp, EBI_CSR1);
		writel(0, EBI_LOCK);
	}
	return 0;
}