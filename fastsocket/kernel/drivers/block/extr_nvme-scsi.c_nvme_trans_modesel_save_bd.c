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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct nvme_ns {int mode_select_num_blocks; scalar_t__ mode_select_block_len; } ;

/* Variables and functions */
 int LONG_DESC_BLOCK ; 
 int SHORT_DESC_BLOCK ; 

__attribute__((used)) static void nvme_trans_modesel_save_bd(struct nvme_ns *ns, u8 *parm_list,
					u16 idx, u16 bd_len, u8 llbaa)
{
	u16 bd_num;

	bd_num = bd_len / ((llbaa == 0) ?
			SHORT_DESC_BLOCK : LONG_DESC_BLOCK);
	/* Store block descriptor info if a FORMAT UNIT comes later */
	/* TODO Saving 1st BD info; what to do if multiple BD received? */
	if (llbaa == 0) {
		/* Standard Block Descriptor - spc4r34 7.5.5.1 */
		ns->mode_select_num_blocks =
				(parm_list[idx + 1] << 16) +
				(parm_list[idx + 2] << 8) +
				(parm_list[idx + 3]);

		ns->mode_select_block_len =
				(parm_list[idx + 5] << 16) +
				(parm_list[idx + 6] << 8) +
				(parm_list[idx + 7]);
	} else {
		/* Long LBA Block Descriptor - sbc3r27 6.4.2.3 */
		ns->mode_select_num_blocks =
				(((u64)parm_list[idx + 0]) << 56) +
				(((u64)parm_list[idx + 1]) << 48) +
				(((u64)parm_list[idx + 2]) << 40) +
				(((u64)parm_list[idx + 3]) << 32) +
				(((u64)parm_list[idx + 4]) << 24) +
				(((u64)parm_list[idx + 5]) << 16) +
				(((u64)parm_list[idx + 6]) << 8) +
				((u64)parm_list[idx + 7]);

		ns->mode_select_block_len =
				(parm_list[idx + 12] << 24) +
				(parm_list[idx + 13] << 16) +
				(parm_list[idx + 14] << 8) +
				(parm_list[idx + 15]);
	}
}