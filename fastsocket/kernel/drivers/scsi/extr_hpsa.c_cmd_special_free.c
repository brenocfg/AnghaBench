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
struct ctlr_info {int /*<<< orphan*/  pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {TYPE_2__ Addr; } ;
struct CommandList {int busaddr; struct CommandList* err_info; TYPE_3__ ErrDesc; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DIRECT_LOOKUP_MASK ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,struct CommandList*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_special_free(struct ctlr_info *h, struct CommandList *c)
{
	union u64bit temp64;

	temp64.val32.lower = c->ErrDesc.Addr.lower;
	temp64.val32.upper = c->ErrDesc.Addr.upper;
	pci_free_consistent(h->pdev, sizeof(*c->err_info),
			    c->err_info, (dma_addr_t) temp64.val);
	pci_free_consistent(h->pdev, sizeof(*c),
			    c, (dma_addr_t) (c->busaddr & DIRECT_LOOKUP_MASK));
}