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
struct super_block {int /*<<< orphan*/  s_umount; scalar_t__ s_root; int /*<<< orphan*/  s_count; int /*<<< orphan*/  s_instances; } ;

/* Variables and functions */
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_super (struct super_block*) ; 
 int /*<<< orphan*/  sb_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pin_sb_for_writeback(struct super_block *sb)
{
	spin_lock(&sb_lock);
	if (list_empty(&sb->s_instances)) {
		spin_unlock(&sb_lock);
		return false;
	}

	sb->s_count++;
	spin_unlock(&sb_lock);

	if (down_read_trylock(&sb->s_umount)) {
		if (sb->s_root)
			return true;
		up_read(&sb->s_umount);
	}

	put_super(sb);
	return false;
}