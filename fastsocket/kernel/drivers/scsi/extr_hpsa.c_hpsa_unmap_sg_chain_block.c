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
union u64bit {int /*<<< orphan*/  val; TYPE_1__ val32; } ;
struct ctlr_info {int max_cmd_sg_entries; int /*<<< orphan*/  pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct SGDescriptor {int /*<<< orphan*/  Len; TYPE_2__ Addr; } ;
struct TYPE_6__ {int SGTotal; } ;
struct CommandList {struct SGDescriptor* SG; TYPE_3__ Header; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_unmap_sg_chain_block(struct ctlr_info *h,
	struct CommandList *c)
{
	struct SGDescriptor *chain_sg;
	union u64bit temp64;

	if (c->Header.SGTotal <= h->max_cmd_sg_entries)
		return;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	temp64.val32.lower = chain_sg->Addr.lower;
	temp64.val32.upper = chain_sg->Addr.upper;
	pci_unmap_single(h->pdev, temp64.val, chain_sg->Len, PCI_DMA_TODEVICE);
}