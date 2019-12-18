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
struct cnic_local {int /*<<< orphan*/  cnic_irq_task; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int drv_state; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int CNIC_DRV_STATE_USING_MSIX ; 
 int cnic_request_irq (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_service_bnx2x_bh ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int cnic_init_bnx2x_irq(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	int err = 0;

	tasklet_init(&cp->cnic_irq_task, cnic_service_bnx2x_bh,
		     (unsigned long) dev);
	if (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX)
		err = cnic_request_irq(dev);

	return err;
}