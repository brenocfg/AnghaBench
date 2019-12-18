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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_count; int /*<<< orphan*/  s_active; } ;
struct inotify_watch {TYPE_1__* inode; int /*<<< orphan*/  wd; } ;
struct inotify_handle {int /*<<< orphan*/  mutex; int /*<<< orphan*/  idr; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_super (struct super_block*) ; 
 int /*<<< orphan*/  get_inotify_watch (struct inotify_watch*) ; 
 struct inotify_watch* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pin_to_kill(struct inotify_handle *ih, struct inotify_watch *watch)
{
	struct super_block *sb = watch->inode->i_sb;
	s32 wd = watch->wd;

	if (atomic_inc_not_zero(&sb->s_active)) {
		get_inotify_watch(watch);
		mutex_unlock(&ih->mutex);
		return 1;	/* the best outcome */
	}
	spin_lock(&sb_lock);
	sb->s_count++;
	spin_unlock(&sb_lock);
	mutex_unlock(&ih->mutex); /* can't grab ->s_umount under it */
	down_read(&sb->s_umount);
	if (likely(!sb->s_root)) {
		/* fs is already shut down; the watch is dead */
		drop_super(sb);
		return 0;
	}
	/* raced with the final deactivate_super() */
	mutex_lock(&ih->mutex);
	if (idr_find(&ih->idr, wd) != watch || watch->inode->i_sb != sb) {
		/* the watch is dead */
		mutex_unlock(&ih->mutex);
		drop_super(sb);
		return 0;
	}
	/* still alive or freed and reused with the same sb and wd; kill */
	get_inotify_watch(watch);
	mutex_unlock(&ih->mutex);
	return 2;
}