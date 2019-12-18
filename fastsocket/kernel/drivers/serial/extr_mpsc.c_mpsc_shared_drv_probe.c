#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ platform_data; } ;
struct platform_device {scalar_t__ id; TYPE_1__ dev; } ;
struct mpsc_shared_pdata {int /*<<< orphan*/  intr_mask_val; int /*<<< orphan*/  intr_cause_val; int /*<<< orphan*/  tcrr_val; int /*<<< orphan*/  rcrr_val; int /*<<< orphan*/  mrr_val; } ;
struct TYPE_4__ {int /*<<< orphan*/  SDMA_INTR_MASK_m; int /*<<< orphan*/  SDMA_INTR_CAUSE_m; int /*<<< orphan*/  MPSC_TCRR_m; int /*<<< orphan*/  MPSC_RCRR_m; int /*<<< orphan*/  MPSC_MRR_m; } ;

/* Variables and functions */
 int ENODEV ; 
 int mpsc_shared_map_regs (struct platform_device*) ; 
 TYPE_2__ mpsc_shared_regs ; 

__attribute__((used)) static int mpsc_shared_drv_probe(struct platform_device *dev)
{
	struct mpsc_shared_pdata	*pdata;
	int				 rc = -ENODEV;

	if (dev->id == 0) {
		if (!(rc = mpsc_shared_map_regs(dev))) {
			pdata = (struct mpsc_shared_pdata *)
				dev->dev.platform_data;

			mpsc_shared_regs.MPSC_MRR_m = pdata->mrr_val;
			mpsc_shared_regs.MPSC_RCRR_m= pdata->rcrr_val;
			mpsc_shared_regs.MPSC_TCRR_m= pdata->tcrr_val;
			mpsc_shared_regs.SDMA_INTR_CAUSE_m =
				pdata->intr_cause_val;
			mpsc_shared_regs.SDMA_INTR_MASK_m =
				pdata->intr_mask_val;

			rc = 0;
		}
	}

	return rc;
}