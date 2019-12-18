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
struct the_nilfs {int /*<<< orphan*/  ns_sufile; } ;
struct TYPE_2__ {int flags; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_nfreesegs; int /*<<< orphan*/  sc_freesegs; TYPE_1__ sc_stage; } ;

/* Variables and functions */
 int NILFS_CF_SUFREED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nilfs_segctor_clear_segment_buffers (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_segctor_free_incomplete_segments (struct nilfs_sc_info*,struct the_nilfs*) ; 
 int nilfs_sufile_cancel_freev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nilfs_segctor_end_construction(struct nilfs_sc_info *sci,
					   struct the_nilfs *nilfs, int err)
{
	if (unlikely(err)) {
		nilfs_segctor_free_incomplete_segments(sci, nilfs);
		if (sci->sc_stage.flags & NILFS_CF_SUFREED) {
			int ret;

			ret = nilfs_sufile_cancel_freev(nilfs->ns_sufile,
							sci->sc_freesegs,
							sci->sc_nfreesegs,
							NULL);
			WARN_ON(ret); /* do not happen */
		}
	}
	nilfs_segctor_clear_segment_buffers(sci);
}