#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_13__ {TYPE_2__ val32; scalar_t__ val; } ;
typedef  TYPE_4__ u64bit ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_14__ {int nr_cmds; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  nr_allocs; scalar_t__ errinfo_pool_dhandle; TYPE_6__* errinfo_pool; scalar_t__ cmd_pool_dhandle; TYPE_6__* cmd_pool; scalar_t__ cmd_pool_bits; } ;
typedef  TYPE_5__ ctlr_info_t ;
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __u32 ;
struct TYPE_10__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_12__ {int Len; TYPE_1__ Addr; } ;
struct TYPE_15__ {int cmdindex; int /*<<< orphan*/  ctlr; TYPE_3__ ErrDesc; scalar_t__ busaddr; int /*<<< orphan*/  list; struct TYPE_15__* err_info; } ;
typedef  int /*<<< orphan*/  ErrorInfo_struct ;
typedef  TYPE_6__ CommandList_struct ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int find_first_zero_bit (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,scalar_t__) ; 

__attribute__((used)) static CommandList_struct *cmd_alloc(ctlr_info_t *h)
{
	CommandList_struct *c;
	int i;
	u64bit temp64;
	dma_addr_t cmd_dma_handle, err_dma_handle;

	do {
		i = find_first_zero_bit(h->cmd_pool_bits, h->nr_cmds);
		if (i == h->nr_cmds)
			return NULL;
	} while (test_and_set_bit(i & (BITS_PER_LONG - 1),
		  h->cmd_pool_bits + (i / BITS_PER_LONG)) != 0);
	c = h->cmd_pool + i;
	memset(c, 0, sizeof(CommandList_struct));
	cmd_dma_handle = h->cmd_pool_dhandle + i * sizeof(CommandList_struct);
	c->err_info = h->errinfo_pool + i;
	memset(c->err_info, 0, sizeof(ErrorInfo_struct));
	err_dma_handle = h->errinfo_pool_dhandle
	    + i * sizeof(ErrorInfo_struct);
	h->nr_allocs++;

	c->cmdindex = i;

	INIT_LIST_HEAD(&c->list);
	c->busaddr = (__u32) cmd_dma_handle;
	temp64.val = (__u64) err_dma_handle;
	c->ErrDesc.Addr.lower = temp64.val32.lower;
	c->ErrDesc.Addr.upper = temp64.val32.upper;
	c->ErrDesc.Len = sizeof(ErrorInfo_struct);

	c->ctlr = h->ctlr;
	return c;
}