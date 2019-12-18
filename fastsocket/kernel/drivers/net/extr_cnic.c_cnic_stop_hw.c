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
struct cnic_local {int /*<<< orphan*/  (* stop_hw ) (struct cnic_dev*) ;int /*<<< orphan*/ * ulp_ops; TYPE_2__* ethdev; int /*<<< orphan*/  (* stop_cm ) (struct cnic_dev*) ;TYPE_1__* udev; } ;
struct cnic_dev {int /*<<< orphan*/  pcidev; int /*<<< orphan*/  flags; struct cnic_local* cnic_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  drv_state; } ;
struct TYPE_3__ {int uio_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_DRV_STATE_HANDLES_IRQ ; 
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 size_t CNIC_ULP_L4 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_cm_shutdown (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_shutdown_rings (struct cnic_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*) ; 
 int /*<<< orphan*/  stub2 (struct cnic_dev*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_stop_hw(struct cnic_dev *dev)
{
	if (test_bit(CNIC_F_CNIC_UP, &dev->flags)) {
		struct cnic_local *cp = dev->cnic_priv;
		int i = 0;

		/* Need to wait for the ring shutdown event to complete
		 * before clearing the CNIC_UP flag.
		 */
		while (cp->udev && cp->udev->uio_dev != -1 && i < 15) {
			msleep(100);
			i++;
		}
		cnic_shutdown_rings(dev);
		cp->stop_cm(dev);
		cp->ethdev->drv_state &= ~CNIC_DRV_STATE_HANDLES_IRQ;
		clear_bit(CNIC_F_CNIC_UP, &dev->flags);
		rcu_assign_pointer(cp->ulp_ops[CNIC_ULP_L4], NULL);
		synchronize_rcu();
		cnic_cm_shutdown(dev);
		cp->stop_hw(dev);
		pci_dev_put(dev->pcidev);
	}
}