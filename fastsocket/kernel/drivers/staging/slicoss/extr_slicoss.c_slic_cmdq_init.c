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
typedef  int u32 ;
struct slic_cmdqueue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ lock; } ;
struct adapter {scalar_t__ state; int slic_handle_ix; TYPE_2__ cmdq_done; TYPE_2__ cmdq_free; TYPE_2__ cmdq_all; } ;

/* Variables and functions */
 scalar_t__ ADAPT_DOWN ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int SLIC_CMDQ_INITPAGES ; 
 int STATUS_FAILURE ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slic_cmdq_addcmdpage (struct adapter*,int*) ; 
 int /*<<< orphan*/  slic_cmdq_free (struct adapter*) ; 
 int* slic_cmdqmem_addpage (struct adapter*) ; 
 int /*<<< orphan*/  slic_cmdqmem_init (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slic_cmdq_init(struct adapter *adapter)
{
	int i;
	u32 *pageaddr;

	ASSERT(adapter->state == ADAPT_DOWN);
	memset(&adapter->cmdq_all, 0, sizeof(struct slic_cmdqueue));
	memset(&adapter->cmdq_free, 0, sizeof(struct slic_cmdqueue));
	memset(&adapter->cmdq_done, 0, sizeof(struct slic_cmdqueue));
	spin_lock_init(&adapter->cmdq_all.lock.lock);
	spin_lock_init(&adapter->cmdq_free.lock.lock);
	spin_lock_init(&adapter->cmdq_done.lock.lock);
	slic_cmdqmem_init(adapter);
	adapter->slic_handle_ix = 1;
	for (i = 0; i < SLIC_CMDQ_INITPAGES; i++) {
		pageaddr = slic_cmdqmem_addpage(adapter);
#ifndef CONFIG_X86_64
		ASSERT(((u32) pageaddr & 0xFFFFF000) == (u32) pageaddr);
#endif
		if (!pageaddr) {
			slic_cmdq_free(adapter);
			return STATUS_FAILURE;
		}
		slic_cmdq_addcmdpage(adapter, pageaddr);
	}
	adapter->slic_handle_ix = 1;

	return STATUS_SUCCESS;
}