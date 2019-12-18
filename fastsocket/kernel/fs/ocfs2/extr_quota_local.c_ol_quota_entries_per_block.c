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
struct super_block {int s_blocksize; } ;
struct ocfs2_local_disk_dqblk {int dummy; } ;

/* Variables and functions */
 int OCFS2_QBLK_RESERVED_SPACE ; 

__attribute__((used)) static inline unsigned int ol_quota_entries_per_block(struct super_block *sb)
{
	return ((sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE) /
		sizeof(struct ocfs2_local_disk_dqblk));
}