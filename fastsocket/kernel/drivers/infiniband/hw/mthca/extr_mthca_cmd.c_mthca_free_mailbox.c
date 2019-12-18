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
struct mthca_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct mthca_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mthca_free_mailbox(struct mthca_dev *dev, struct mthca_mailbox *mailbox)
{
	if (!mailbox)
		return;

	pci_pool_free(dev->cmd.pool, mailbox->buf, mailbox->dma);
	kfree(mailbox);
}