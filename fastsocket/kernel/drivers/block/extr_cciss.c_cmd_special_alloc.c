#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_15__ {TYPE_2__ val32; scalar_t__ val; } ;
typedef  TYPE_4__ u64bit ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_16__ {int /*<<< orphan*/  ctlr; int /*<<< orphan*/  pdev; } ;
typedef  TYPE_5__ ctlr_info_t ;
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __u32 ;
struct TYPE_12__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_14__ {int Len; TYPE_1__ Addr; } ;
struct TYPE_17__ {int cmdindex; int /*<<< orphan*/  ctlr; TYPE_3__ ErrDesc; scalar_t__ busaddr; int /*<<< orphan*/  list; struct TYPE_17__* err_info; } ;
typedef  TYPE_6__ ErrorInfo_struct ;
typedef  TYPE_6__ CommandList_struct ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static CommandList_struct *cmd_special_alloc(ctlr_info_t *h)
{
	CommandList_struct *c;
	u64bit temp64;
	dma_addr_t cmd_dma_handle, err_dma_handle;

	c = (CommandList_struct *) pci_alloc_consistent(h->pdev,
		sizeof(CommandList_struct), &cmd_dma_handle);
	if (c == NULL)
		return NULL;
	memset(c, 0, sizeof(CommandList_struct));

	c->cmdindex = -1;

	c->err_info = (ErrorInfo_struct *)
	    pci_alloc_consistent(h->pdev, sizeof(ErrorInfo_struct),
		    &err_dma_handle);

	if (c->err_info == NULL) {
		pci_free_consistent(h->pdev,
			sizeof(CommandList_struct), c, cmd_dma_handle);
		return NULL;
	}
	memset(c->err_info, 0, sizeof(ErrorInfo_struct));

	INIT_LIST_HEAD(&c->list);
	c->busaddr = (__u32) cmd_dma_handle;
	temp64.val = (__u64) err_dma_handle;
	c->ErrDesc.Addr.lower = temp64.val32.lower;
	c->ErrDesc.Addr.upper = temp64.val32.upper;
	c->ErrDesc.Len = sizeof(ErrorInfo_struct);

	c->ctlr = h->ctlr;
	return c;
}