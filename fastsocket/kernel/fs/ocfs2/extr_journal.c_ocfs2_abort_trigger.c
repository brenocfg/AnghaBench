#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jbd2_buffer_trigger_type {int dummy; } ;
struct buffer_head {TYPE_2__* b_assoc_map; scalar_t__ b_blocknr; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ocfs2_abort_trigger(struct jbd2_buffer_trigger_type *triggers,
				struct buffer_head *bh)
{
	mlog(ML_ERROR,
	     "ocfs2_abort_trigger called by JBD2.  bh = 0x%lx, "
	     "bh->b_blocknr = %llu\n",
	     (unsigned long)bh,
	     (unsigned long long)bh->b_blocknr);

	/* We aren't guaranteed to have the superblock here - but if we
	 * don't, it'll just crash. */
	ocfs2_error(bh->b_assoc_map->host->i_sb,
		    "JBD2 has aborted our journal, ocfs2 cannot continue\n");
}