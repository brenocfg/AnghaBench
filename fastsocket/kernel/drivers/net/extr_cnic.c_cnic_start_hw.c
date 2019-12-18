#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  gen; } ;
struct cnic_local {int (* alloc_resc ) (struct cnic_dev*) ;int (* start_hw ) (struct cnic_dev*) ;int /*<<< orphan*/  (* free_resc ) (struct cnic_dev*) ;int /*<<< orphan*/  (* enable_int ) (struct cnic_dev*) ;int /*<<< orphan*/  status_blk_num; TYPE_1__ status_blk; int /*<<< orphan*/  func; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {TYPE_2__* irq_arr; int /*<<< orphan*/  io_base; } ;
struct cnic_dev {TYPE_3__* pcidev; int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; int /*<<< orphan*/  regview; struct cnic_local* cnic_priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  devfn; } ;
struct TYPE_6__ {int /*<<< orphan*/  status_blk_num; int /*<<< orphan*/  status_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int EALREADY ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int cnic_cm_open (struct cnic_dev*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_dev_get (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_3__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct cnic_dev*) ; 
 int stub2 (struct cnic_dev*) ; 
 int /*<<< orphan*/  stub3 (struct cnic_dev*) ; 
 int /*<<< orphan*/  stub4 (struct cnic_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_start_hw(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	int err;

	if (test_bit(CNIC_F_CNIC_UP, &dev->flags))
		return -EALREADY;

	dev->regview = ethdev->io_base;
	pci_dev_get(dev->pcidev);
	cp->func = PCI_FUNC(dev->pcidev->devfn);
	cp->status_blk.gen = ethdev->irq_arr[0].status_blk;
	cp->status_blk_num = ethdev->irq_arr[0].status_blk_num;

	err = cp->alloc_resc(dev);
	if (err) {
		netdev_err(dev->netdev, "allocate resource failure\n");
		goto err1;
	}

	err = cp->start_hw(dev);
	if (err)
		goto err1;

	err = cnic_cm_open(dev);
	if (err)
		goto err1;

	set_bit(CNIC_F_CNIC_UP, &dev->flags);

	cp->enable_int(dev);

	return 0;

err1:
	cp->free_resc(dev);
	pci_dev_put(dev->pcidev);
	return err;
}