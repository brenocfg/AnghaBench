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
struct TYPE_2__ {scalar_t__ nblocks; int /*<<< orphan*/  flags; } ;
struct nilfs_segment_buffer {scalar_t__ sb_rest_blocks; TYPE_1__ sb_sum; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_super_root; struct nilfs_segment_buffer* sc_curseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SS_SR ; 
 scalar_t__ likely (int) ; 
 int nilfs_segbuf_extend_payload (struct nilfs_segment_buffer*,int /*<<< orphan*/ *) ; 
 int nilfs_segctor_feed_segment (struct nilfs_sc_info*) ; 

__attribute__((used)) static int nilfs_segctor_add_super_root(struct nilfs_sc_info *sci)
{
	struct nilfs_segment_buffer *segbuf = sci->sc_curseg;
	int err;

	if (segbuf->sb_sum.nblocks >= segbuf->sb_rest_blocks) {
		err = nilfs_segctor_feed_segment(sci);
		if (err)
			return err;
		segbuf = sci->sc_curseg;
	}
	err = nilfs_segbuf_extend_payload(segbuf, &sci->sc_super_root);
	if (likely(!err))
		segbuf->sb_sum.flags |= NILFS_SS_SR;
	return err;
}