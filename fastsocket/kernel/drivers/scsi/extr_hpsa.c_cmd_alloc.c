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
struct TYPE_5__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
union u64bit {TYPE_2__ val32; scalar_t__ val; } ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ctlr_info {int nr_cmds; scalar_t__ errinfo_pool_dhandle; struct CommandList* errinfo_pool; scalar_t__ cmd_pool_dhandle; struct CommandList* cmd_pool; int /*<<< orphan*/  lock; scalar_t__ cmd_pool_bits; } ;
struct TYPE_4__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {int Len; TYPE_1__ Addr; } ;
struct CommandList {int cmdindex; struct ctlr_info* h; TYPE_3__ ErrDesc; scalar_t__ busaddr; int /*<<< orphan*/  list; struct CommandList* err_info; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int find_first_zero_bit (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct CommandList*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int,scalar_t__) ; 

__attribute__((used)) static struct CommandList *cmd_alloc(struct ctlr_info *h)
{
	struct CommandList *c;
	int i;
	union u64bit temp64;
	dma_addr_t cmd_dma_handle, err_dma_handle;
	unsigned long flags;

	spin_lock_irqsave(&h->lock, flags);
	do {
		i = find_first_zero_bit(h->cmd_pool_bits, h->nr_cmds);
		if (i == h->nr_cmds) {
			spin_unlock_irqrestore(&h->lock, flags);
			return NULL;
		}
	} while (test_and_set_bit
		 (i & (BITS_PER_LONG - 1),
		  h->cmd_pool_bits + (i / BITS_PER_LONG)) != 0);
	spin_unlock_irqrestore(&h->lock, flags);

	c = h->cmd_pool + i;
	memset(c, 0, sizeof(*c));
	cmd_dma_handle = h->cmd_pool_dhandle
	    + i * sizeof(*c);
	c->err_info = h->errinfo_pool + i;
	memset(c->err_info, 0, sizeof(*c->err_info));
	err_dma_handle = h->errinfo_pool_dhandle
	    + i * sizeof(*c->err_info);

	c->cmdindex = i;

	INIT_LIST_HEAD(&c->list);
	c->busaddr = (u32) cmd_dma_handle;
	temp64.val = (u64) err_dma_handle;
	c->ErrDesc.Addr.lower = temp64.val32.lower;
	c->ErrDesc.Addr.upper = temp64.val32.upper;
	c->ErrDesc.Len = sizeof(*c->err_info);

	c->h = h;
	return c;
}