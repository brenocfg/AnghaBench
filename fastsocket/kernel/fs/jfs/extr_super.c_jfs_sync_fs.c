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
struct super_block {int dummy; } ;
struct jfs_log {int dummy; } ;
struct TYPE_2__ {struct jfs_log* log; } ;

/* Variables and functions */
 TYPE_1__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  jfs_flush_journal (struct jfs_log*,int) ; 
 int /*<<< orphan*/  jfs_syncpt (struct jfs_log*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_sync_fs(struct super_block *sb, int wait)
{
	struct jfs_log *log = JFS_SBI(sb)->log;

	/* log == NULL indicates read-only mount */
	if (log) {
		jfs_flush_journal(log, wait);
		jfs_syncpt(log, 0);
	}

	return 0;
}