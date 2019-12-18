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
struct TYPE_2__ {int simmediate; } ;
union mips_instruction {TYPE_1__ i_format; } ;
struct mips_frame_info {int func_size; int pc_offset; int frame_size; union mips_instruction* func; } ;

/* Variables and functions */
 scalar_t__ is_jal_jalr_jr_ins (union mips_instruction*) ; 
 scalar_t__ is_ra_save_ins (union mips_instruction*) ; 
 scalar_t__ is_sp_move_ins (union mips_instruction*) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int get_frame_info(struct mips_frame_info *info)
{
	union mips_instruction *ip = info->func;
	unsigned max_insns = info->func_size / sizeof(union mips_instruction);
	unsigned i;

	info->pc_offset = -1;
	info->frame_size = 0;

	if (!ip)
		goto err;

	if (max_insns == 0)
		max_insns = 128U;	/* unknown function size */
	max_insns = min(128U, max_insns);

	for (i = 0; i < max_insns; i++, ip++) {

		if (is_jal_jalr_jr_ins(ip))
			break;
		if (!info->frame_size) {
			if (is_sp_move_ins(ip))
				info->frame_size = - ip->i_format.simmediate;
			continue;
		}
		if (info->pc_offset == -1 && is_ra_save_ins(ip)) {
			info->pc_offset =
				ip->i_format.simmediate / sizeof(long);
			break;
		}
	}
	if (info->frame_size && info->pc_offset >= 0) /* nested */
		return 0;
	if (info->pc_offset < 0) /* leaf */
		return 1;
	/* prologue seems boggus... */
err:
	return -1;
}