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
struct pci_dev {int dummy; } ;
struct driver_data {int /*<<< orphan*/  remove_list; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/  online_list; } ;

/* Variables and functions */
 int MTIP_ABAR ; 
 int /*<<< orphan*/  MTIP_DDF_CLEANUP_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 int /*<<< orphan*/  dev_lock ; 
 int /*<<< orphan*/  kfree (struct driver_data*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtip_block_remove (struct driver_data*) ; 
 scalar_t__ mtip_check_surprise_removal (struct pci_dev*) ; 
 int /*<<< orphan*/  mtip_command_cleanup (struct driver_data*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct driver_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iounmap_regions (struct pci_dev*,int) ; 
 int /*<<< orphan*/  removing_list ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtip_pci_remove(struct pci_dev *pdev)
{
	struct driver_data *dd = pci_get_drvdata(pdev);
	int counter = 0;
	unsigned long flags;

	set_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->online_list);
	list_add(&dd->remove_list, &removing_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	if (mtip_check_surprise_removal(pdev)) {
		while (!test_bit(MTIP_DDF_CLEANUP_BIT, &dd->dd_flag)) {
			counter++;
			msleep(20);
			if (counter == 10) {
				/* Cleanup the outstanding commands */
				mtip_command_cleanup(dd);
				break;
			}
		}
	}

	/* Clean up the block layer. */
	mtip_block_remove(dd);

	pci_disable_msi(pdev);

	spin_lock_irqsave(&dev_lock, flags);
	list_del_init(&dd->remove_list);
	spin_unlock_irqrestore(&dev_lock, flags);

	kfree(dd);
	pcim_iounmap_regions(pdev, 1 << MTIP_ABAR);
}