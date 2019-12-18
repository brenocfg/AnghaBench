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
struct TYPE_2__ {scalar_t__ lock_depth; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  reiserfs_panic (struct super_block*,char*,char*,char*) ; 

void reiserfs_check_lock_depth(struct super_block *sb, char *caller)
{
#ifdef CONFIG_SMP
	if (current->lock_depth < 0) {
		reiserfs_panic(sb, "journal-1", "%s called without kernel "
			       "lock held", caller);
	}
#else
	;
#endif
}