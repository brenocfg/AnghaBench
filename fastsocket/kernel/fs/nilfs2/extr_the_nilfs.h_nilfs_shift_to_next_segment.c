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
struct the_nilfs {int /*<<< orphan*/  ns_seg_seq; scalar_t__ ns_pseg_offset; int /*<<< orphan*/  ns_nextnum; int /*<<< orphan*/  ns_segnum; } ;

/* Variables and functions */

__attribute__((used)) static inline void nilfs_shift_to_next_segment(struct the_nilfs *nilfs)
{
	/* move forward with a full segment */
	nilfs->ns_segnum = nilfs->ns_nextnum;
	nilfs->ns_pseg_offset = 0;
	nilfs->ns_seg_seq++;
}