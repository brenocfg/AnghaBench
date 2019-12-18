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
typedef  int /*<<< orphan*/  tid_t ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 scalar_t__ journal_start_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_wait_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_sync_fs (struct super_block*,int) ; 

__attribute__((used)) static int ext3_sync_fs(struct super_block *sb, int wait)
{
	tid_t target;

	trace_ext3_sync_fs(sb, wait);
	if (journal_start_commit(EXT3_SB(sb)->s_journal, &target)) {
		if (wait)
			log_wait_commit(EXT3_SB(sb)->s_journal, target);
	}
	return 0;
}