#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct ctlr_info {size_t max_cmd_sg_entries; int /*<<< orphan*/  pdev; struct SGDescriptor** cmd_sg_list; } ;
struct TYPE_4__ {void* upper; void* lower; } ;
struct SGDescriptor {int Len; TYPE_2__ Addr; int /*<<< orphan*/  Ext; } ;
struct TYPE_3__ {int SGTotal; } ;
struct CommandList {size_t cmdindex; TYPE_1__ Header; struct SGDescriptor* SG; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSA_SG_CHAIN ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int pci_map_single (int /*<<< orphan*/ ,struct SGDescriptor*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_map_sg_chain_block(struct ctlr_info *h,
	struct CommandList *c)
{
	struct SGDescriptor *chain_sg, *chain_block;
	u64 temp64;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	chain_block = h->cmd_sg_list[c->cmdindex];
	chain_sg->Ext = HPSA_SG_CHAIN;
	chain_sg->Len = sizeof(*chain_sg) *
		(c->Header.SGTotal - h->max_cmd_sg_entries);
	temp64 = pci_map_single(h->pdev, chain_block, chain_sg->Len,
				PCI_DMA_TODEVICE);
	chain_sg->Addr.lower = (u32) (temp64 & 0x0FFFFFFFFULL);
	chain_sg->Addr.upper = (u32) ((temp64 >> 32) & 0x0FFFFFFFFULL);
}