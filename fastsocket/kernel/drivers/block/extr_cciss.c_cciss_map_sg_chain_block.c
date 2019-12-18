#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_13__ {TYPE_2__ val32; int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ u64bit ;
struct TYPE_14__ {int max_cmd_sgentries; int /*<<< orphan*/  pdev; } ;
typedef  TYPE_4__ ctlr_info_t ;
struct TYPE_16__ {TYPE_5__* SG; } ;
struct TYPE_11__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_15__ {int Len; TYPE_1__ Addr; int /*<<< orphan*/  Ext; } ;
typedef  TYPE_5__ SGDescriptor_struct ;
typedef  TYPE_6__ CommandList_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CCISS_SG_CHAIN ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cciss_map_sg_chain_block(ctlr_info_t *h, CommandList_struct *c,
	SGDescriptor_struct *chain_block, int len)
{
	SGDescriptor_struct *chain_sg;
	u64bit temp64;

	chain_sg = &c->SG[h->max_cmd_sgentries - 1];
	chain_sg->Ext = CCISS_SG_CHAIN;
	chain_sg->Len = len;
	temp64.val = pci_map_single(h->pdev, chain_block, len,
				PCI_DMA_TODEVICE);
	chain_sg->Addr.lower = temp64.val32.lower;
	chain_sg->Addr.upper = temp64.val32.upper;
}