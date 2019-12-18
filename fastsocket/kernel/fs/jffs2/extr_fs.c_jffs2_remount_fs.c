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
struct super_block {int s_flags; } ;
struct jffs2_sb_info {int flags; int /*<<< orphan*/  alloc_sem; } ;

/* Variables and functions */
 int EROFS ; 
 int JFFS2_SB_FLAG_RO ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (struct super_block*) ; 
 int MS_NOATIME ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  jffs2_flush_wbuf_pad (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_start_garbage_collect_thread (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_stop_garbage_collect_thread (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int jffs2_remount_fs (struct super_block *sb, int *flags, char *data)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(sb);

	if (c->flags & JFFS2_SB_FLAG_RO && !(sb->s_flags & MS_RDONLY))
		return -EROFS;

	/* We stop if it was running, then restart if it needs to.
	   This also catches the case where it was stopped and this
	   is just a remount to restart it.
	   Flush the writebuffer, if neccecary, else we loose it */
	lock_kernel();
	if (!(sb->s_flags & MS_RDONLY)) {
		jffs2_stop_garbage_collect_thread(c);
		mutex_lock(&c->alloc_sem);
		jffs2_flush_wbuf_pad(c);
		mutex_unlock(&c->alloc_sem);
	}

	if (!(*flags & MS_RDONLY))
		jffs2_start_garbage_collect_thread(c);

	*flags |= MS_NOATIME;

	unlock_kernel();
	return 0;
}