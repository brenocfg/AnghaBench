#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
union u64bit {scalar_t__ val; TYPE_1__ val32; } ;
struct pci_dev {int dummy; } ;
struct CommandList {TYPE_3__* SG; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {int /*<<< orphan*/  Len; TYPE_2__ Addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpsa_pci_unmap(struct pci_dev *pdev,
	struct CommandList *c, int sg_used, int data_direction)
{
	int i;
	union u64bit addr64;

	for (i = 0; i < sg_used; i++) {
		addr64.val32.lower = c->SG[i].Addr.lower;
		addr64.val32.upper = c->SG[i].Addr.upper;
		pci_unmap_single(pdev, (dma_addr_t) addr64.val, c->SG[i].Len,
			data_direction);
	}
}