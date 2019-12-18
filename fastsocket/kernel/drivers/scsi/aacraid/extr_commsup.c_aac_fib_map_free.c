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
struct aac_dev {int max_fib_size; scalar_t__ hw_fib_pa; int /*<<< orphan*/ * hw_fib_va; TYPE_1__* scsi_host_ptr; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 int AAC_NUM_MGT_FIB ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

void aac_fib_map_free(struct aac_dev *dev)
{
	pci_free_consistent(dev->pdev,
	  dev->max_fib_size * (dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB),
	  dev->hw_fib_va, dev->hw_fib_pa);
	dev->hw_fib_va = NULL;
	dev->hw_fib_pa = 0;
}