#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct iwl_trans {int dummy; } ;
struct iwl_test {struct iwl_trans* trans; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_WADDR ; 
 int /*<<< orphan*/  HBUS_TARG_PRPH_WDAT ; 
 scalar_t__ IWL_ABS_PRPH_START ; 
 scalar_t__ PRPH_END ; 
 scalar_t__ iwl_test_valid_hw_addr (struct iwl_test*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,int,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_write_mem (struct iwl_trans*,scalar_t__,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char*,scalar_t__) ; 

__attribute__((used)) static int iwl_test_indirect_write(struct iwl_test *tst, u32 addr,
	u32 size, unsigned char *buf)
{
	struct iwl_trans *trans = tst->trans;
	u32 val, i;
	unsigned long flags;

	if (IWL_ABS_PRPH_START <= addr &&
	    addr < IWL_ABS_PRPH_START + PRPH_END) {
		/* Periphery writes can be 1-3 bytes long, or DWORDs */
		if (size < 4) {
			memcpy(&val, buf, size);
			if (!iwl_trans_grab_nic_access(trans, false, &flags))
					return -EIO;
			iwl_write32(trans, HBUS_TARG_PRPH_WADDR,
				    (addr & 0x0000FFFF) |
				    ((size - 1) << 24));
			iwl_write32(trans, HBUS_TARG_PRPH_WDAT, val);
			iwl_trans_release_nic_access(trans, &flags);
		} else {
			if (size % 4)
				return -EINVAL;
			for (i = 0; i < size; i += 4)
				iwl_write_prph(trans, addr+i,
					       *(u32 *)(buf+i));
		}
	} else if (iwl_test_valid_hw_addr(tst, addr)) {
		iwl_trans_write_mem(trans, addr, buf, size / 4);
	} else {
		return -EINVAL;
	}
	return 0;
}