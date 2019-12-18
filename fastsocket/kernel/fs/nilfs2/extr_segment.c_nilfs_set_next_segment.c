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
struct the_nilfs {int /*<<< orphan*/  ns_ctime; int /*<<< orphan*/  ns_seg_seq; scalar_t__ ns_pseg_offset; int /*<<< orphan*/  ns_nextnum; int /*<<< orphan*/  ns_segnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctime; int /*<<< orphan*/  seg_seq; scalar_t__ nblocks; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; scalar_t__ sb_fseg_start; scalar_t__ sb_pseg_start; int /*<<< orphan*/  sb_nextnum; int /*<<< orphan*/  sb_segnum; } ;

/* Variables and functions */

__attribute__((used)) static void nilfs_set_next_segment(struct the_nilfs *nilfs,
				   struct nilfs_segment_buffer *segbuf)
{
	nilfs->ns_segnum = segbuf->sb_segnum;
	nilfs->ns_nextnum = segbuf->sb_nextnum;
	nilfs->ns_pseg_offset = segbuf->sb_pseg_start - segbuf->sb_fseg_start
		+ segbuf->sb_sum.nblocks;
	nilfs->ns_seg_seq = segbuf->sb_sum.seg_seq;
	nilfs->ns_ctime = segbuf->sb_sum.ctime;
}