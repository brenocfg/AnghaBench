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
struct nilfs_segment_usage {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_mdt_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int nilfs_sufile_get_segment_usage (struct inode*,int /*<<< orphan*/ ,struct nilfs_segment_usage**,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_sufile_put_segment_usage (struct inode*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_touch_segusage(struct inode *sufile, __u64 segnum)
{
	struct buffer_head *bh_su;
	struct nilfs_segment_usage *raw_su;
	int err;

	err = nilfs_sufile_get_segment_usage(sufile, segnum, &raw_su, &bh_su);
	if (unlikely(err))
		return err;
	nilfs_mdt_mark_buffer_dirty(bh_su);
	nilfs_mdt_mark_dirty(sufile);
	nilfs_sufile_put_segment_usage(sufile, segnum, bh_su);
	return 0;
}