#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {scalar_t__ id; } ;
struct TYPE_2__ {scalar_t__ SDMA_INTR_MASK_m; scalar_t__ SDMA_INTR_CAUSE_m; scalar_t__ MPSC_TCRR_m; scalar_t__ MPSC_RCRR_m; scalar_t__ MPSC_MRR_m; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__ mpsc_shared_regs ; 
 int /*<<< orphan*/  mpsc_shared_unmap_regs () ; 

__attribute__((used)) static int mpsc_shared_drv_remove(struct platform_device *dev)
{
	int	rc = -ENODEV;

	if (dev->id == 0) {
		mpsc_shared_unmap_regs();
		mpsc_shared_regs.MPSC_MRR_m = 0;
		mpsc_shared_regs.MPSC_RCRR_m = 0;
		mpsc_shared_regs.MPSC_TCRR_m = 0;
		mpsc_shared_regs.SDMA_INTR_CAUSE_m = 0;
		mpsc_shared_regs.SDMA_INTR_MASK_m = 0;
		rc = 0;
	}

	return rc;
}