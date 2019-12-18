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
struct super_operations {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqptr_sem; int /*<<< orphan*/  dqonoff_mutex; int /*<<< orphan*/  dqio_mutex; } ;
struct super_block {int s_count; int s_time_gran; struct super_operations const* s_op; int /*<<< orphan*/  s_qcop; int /*<<< orphan*/  dq_op; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/  s_wait_unfrozen; TYPE_1__ s_dquot; int /*<<< orphan*/  s_vfs_rename_mutex; int /*<<< orphan*/  s_active; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_dentry_lru; int /*<<< orphan*/  s_inodes; int /*<<< orphan*/  s_anon; int /*<<< orphan*/  s_instances; int /*<<< orphan*/  s_files; } ;
struct file_system_type {int /*<<< orphan*/  s_lock_key; int /*<<< orphan*/  s_umount_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_NON_LFS ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroy_sb_writers (struct super_block*) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 scalar_t__ init_sb_writers (struct super_block*,struct file_system_type*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct super_block*) ; 
 struct super_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_dquot_ops ; 
 int /*<<< orphan*/  sb_quotactl_ops ; 
 scalar_t__ security_sb_alloc (struct super_block*) ; 
 int /*<<< orphan*/  security_sb_free (struct super_block*) ; 

__attribute__((used)) static struct super_block *alloc_super(struct file_system_type *type)
{
	struct super_block *s = kzalloc(sizeof(struct super_block),  GFP_USER);
	static const struct super_operations default_op;

	if (s) {
		if (security_sb_alloc(s)) {
			/*
			 * We cannot call security_sb_free() without
			 * security_sb_alloc() succeeding. So bail out manually
			 */
			kfree(s);
			s = NULL;
			goto out;
		}
		INIT_LIST_HEAD(&s->s_files);
		if (init_sb_writers(s, type))
			goto err_out;
		INIT_LIST_HEAD(&s->s_instances);
		INIT_HLIST_HEAD(&s->s_anon);
		INIT_LIST_HEAD(&s->s_inodes);
		INIT_LIST_HEAD(&s->s_dentry_lru);
		init_rwsem(&s->s_umount);
		mutex_init(&s->s_lock);
		lockdep_set_class(&s->s_umount, &type->s_umount_key);
		/*
		 * The locking rules for s_lock are up to the
		 * filesystem. For example ext3fs has different
		 * lock ordering than usbfs:
		 */
		lockdep_set_class(&s->s_lock, &type->s_lock_key);
		/*
		 * sget() can have s_umount recursion.
		 *
		 * When it cannot find a suitable sb, it allocates a new
		 * one (this one), and tries again to find a suitable old
		 * one.
		 *
		 * In case that succeeds, it will acquire the s_umount
		 * lock of the old one. Since these are clearly distrinct
		 * locks, and this object isn't exposed yet, there's no
		 * risk of deadlocks.
		 *
		 * Annotate this by putting this lock in a different
		 * subclass.
		 */
		down_write_nested(&s->s_umount, SINGLE_DEPTH_NESTING);
		s->s_count = 1;
		atomic_set(&s->s_active, 1);
		mutex_init(&s->s_vfs_rename_mutex);
		mutex_init(&s->s_dquot.dqio_mutex);
		mutex_init(&s->s_dquot.dqonoff_mutex);
		init_rwsem(&s->s_dquot.dqptr_sem);
		init_waitqueue_head(&s->s_wait_unfrozen);
		s->s_maxbytes = MAX_NON_LFS;
		s->dq_op = sb_dquot_ops;
		s->s_qcop = sb_quotactl_ops;
		s->s_op = &default_op;
		s->s_time_gran = 1000000000;
	}
out:
	return s;
err_out:
	security_sb_free(s);
	destroy_sb_writers(s);
	kfree(s);
	s = NULL;
	goto out;
}