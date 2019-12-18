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
typedef  int u64 ;
struct nilfs_super_block {int /*<<< orphan*/  s_log_block_size; int /*<<< orphan*/  s_blocks_per_segment; int /*<<< orphan*/  s_nsegments; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_sb2_bad_offset(struct nilfs_super_block *sbp, u64 offset)
{
	return offset < ((le64_to_cpu(sbp->s_nsegments) *
			  le32_to_cpu(sbp->s_blocks_per_segment)) <<
			 (le32_to_cpu(sbp->s_log_block_size) + 10));
}