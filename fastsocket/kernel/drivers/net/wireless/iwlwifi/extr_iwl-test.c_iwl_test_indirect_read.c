#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_trans {int dummy; } ;
struct TYPE_2__ {int size; int in_read; int /*<<< orphan*/  nchunks; int /*<<< orphan*/ * addr; } ;
struct iwl_test {TYPE_1__ mem; struct iwl_trans* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMP_CHUNK_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_RADDR ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_RDAT ; 
 int IWL_ABS_PRPH_START ; 
 int PRPH_END ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,int,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_read_mem (struct iwl_trans*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_test_indirect_read(struct iwl_test *tst, u32 addr, u32 size)
{
	struct iwl_trans *trans = tst->trans;
	unsigned long flags;
	int i;

	if (size & 0x3)
		return -EINVAL;

	tst->mem.size = size;
	tst->mem.addr = kmalloc(tst->mem.size, GFP_KERNEL);
	if (tst->mem.addr == NULL)
		return -ENOMEM;

	/* Hard-coded periphery absolute address */
	if (IWL_ABS_PRPH_START <= addr &&
	    addr < IWL_ABS_PRPH_START + PRPH_END) {
			if (!iwl_trans_grab_nic_access(trans, false, &flags)) {
				return -EIO;
			}
			iwl_write32(trans, HBUS_TARG_PRPH_RADDR,
				    addr | (3 << 24));
			for (i = 0; i < size; i += 4)
				*(u32 *)(tst->mem.addr + i) =
					iwl_read32(trans, HBUS_TARG_PRPH_RDAT);
			iwl_trans_release_nic_access(trans, &flags);
	} else { /* target memory (SRAM) */
		iwl_trans_read_mem(trans, addr, tst->mem.addr,
				   tst->mem.size / 4);
	}

	tst->mem.nchunks =
		DIV_ROUND_UP(tst->mem.size, DUMP_CHUNK_SIZE);
	tst->mem.in_read = true;
	return 0;

}