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
struct super_block {scalar_t__ s_count; int /*<<< orphan*/  s_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __put_super (struct super_block*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int __put_super_and_need_restart(struct super_block *sb)
{
	/* check for race with generic_shutdown_super() */
	if (list_empty(&sb->s_list)) {
		/* super block is removed, need to restart... */
		__put_super(sb);
		return 1;
	}
	/* can't be the last, since s_list is still in use */
	sb->s_count--;
	BUG_ON(sb->s_count == 0);
	return 0;
}