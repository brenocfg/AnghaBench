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
struct TYPE_2__ {int flags; int /*<<< orphan*/  dbell_map; int /*<<< orphan*/  pool; } ;
struct mthca_dev {TYPE_1__ cmd; int /*<<< orphan*/  hcr; } ;

/* Variables and functions */
 int MTHCA_CMD_POST_DOORBELLS ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ ) ; 

void mthca_cmd_cleanup(struct mthca_dev *dev)
{
	pci_pool_destroy(dev->cmd.pool);
	iounmap(dev->hcr);
	if (dev->cmd.flags & MTHCA_CMD_POST_DOORBELLS)
		iounmap(dev->cmd.dbell_map);
}