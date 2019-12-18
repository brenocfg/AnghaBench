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
struct TYPE_2__ {int /*<<< orphan*/  pool; scalar_t__ flags; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/  hcr_mutex; } ;
struct mthca_dev {int /*<<< orphan*/  hcr; TYPE_1__ cmd; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MTHCA_HCR_BASE ; 
 int /*<<< orphan*/  MTHCA_HCR_SIZE ; 
 int /*<<< orphan*/  MTHCA_MAILBOX_SIZE ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

int mthca_cmd_init(struct mthca_dev *dev)
{
	mutex_init(&dev->cmd.hcr_mutex);
	sema_init(&dev->cmd.poll_sem, 1);
	dev->cmd.flags = 0;

	dev->hcr = ioremap(pci_resource_start(dev->pdev, 0) + MTHCA_HCR_BASE,
			   MTHCA_HCR_SIZE);
	if (!dev->hcr) {
		mthca_err(dev, "Couldn't map command register.");
		return -ENOMEM;
	}

	dev->cmd.pool = pci_pool_create("mthca_cmd", dev->pdev,
					MTHCA_MAILBOX_SIZE,
					MTHCA_MAILBOX_SIZE, 0);
	if (!dev->cmd.pool) {
		iounmap(dev->hcr);
		return -ENOMEM;
	}

	return 0;
}