#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mthca_mailbox {scalar_t__ buf; } ;
struct mthca_eq_context {int dummy; } ;
struct mthca_eq {int nent; TYPE_2__* page_list; int /*<<< orphan*/  mr; int /*<<< orphan*/  eqn; int /*<<< orphan*/  eqn_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  arm_mask; } ;
struct mthca_dev {int /*<<< orphan*/  pdev; TYPE_1__ eq_table; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int MTHCA_EQ_ENTRY_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  be32_to_cpup (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mapping ; 
 int mthca_HW2SW_EQ (struct mthca_dev*,struct mthca_mailbox*,int /*<<< orphan*/ ) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 int /*<<< orphan*/  mthca_free_mr (struct mthca_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void mthca_free_eq(struct mthca_dev *dev,
			  struct mthca_eq *eq)
{
	struct mthca_mailbox *mailbox;
	int err;
	int npages = (eq->nent * MTHCA_EQ_ENTRY_SIZE + PAGE_SIZE - 1) /
		PAGE_SIZE;
	int i;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return;

	err = mthca_HW2SW_EQ(dev, mailbox, eq->eqn);
	if (err)
		mthca_warn(dev, "HW2SW_EQ returned %d\n", err);

	dev->eq_table.arm_mask &= ~eq->eqn_mask;

	if (0) {
		mthca_dbg(dev, "Dumping EQ context %02x:\n", eq->eqn);
		for (i = 0; i < sizeof (struct mthca_eq_context) / 4; ++i) {
			if (i % 4 == 0)
				printk("[%02x] ", i * 4);
			printk(" %08x", be32_to_cpup(mailbox->buf + i * 4));
			if ((i + 1) % 4 == 0)
				printk("\n");
		}
	}

	mthca_free_mr(dev, &eq->mr);
	for (i = 0; i < npages; ++i)
		pci_free_consistent(dev->pdev, PAGE_SIZE,
				    eq->page_list[i].buf,
				    pci_unmap_addr(&eq->page_list[i], mapping));

	kfree(eq->page_list);
	mthca_free_mailbox(dev, mailbox);
}