#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_13__ {int /*<<< orphan*/  val; TYPE_1__ val32; } ;
typedef  TYPE_4__ u64bit ;
struct TYPE_14__ {int max_cmd_sgentries; int /*<<< orphan*/  pdev; } ;
typedef  TYPE_5__ ctlr_info_t ;
struct TYPE_12__ {int SGTotal; } ;
struct TYPE_16__ {TYPE_6__* SG; TYPE_3__ Header; } ;
struct TYPE_11__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_15__ {int /*<<< orphan*/  Len; TYPE_2__ Addr; } ;
typedef  TYPE_6__ SGDescriptor_struct ;
typedef  TYPE_7__ CommandList_struct ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cciss_unmap_sg_chain_block(ctlr_info_t *h, CommandList_struct *c)
{
	SGDescriptor_struct *chain_sg;
	u64bit temp64;

	if (c->Header.SGTotal <= h->max_cmd_sgentries)
		return;

	chain_sg = &c->SG[h->max_cmd_sgentries - 1];
	temp64.val32.lower = chain_sg->Addr.lower;
	temp64.val32.upper = chain_sg->Addr.upper;
	pci_unmap_single(h->pdev, temp64.val, chain_sg->Len, PCI_DMA_TODEVICE);
}