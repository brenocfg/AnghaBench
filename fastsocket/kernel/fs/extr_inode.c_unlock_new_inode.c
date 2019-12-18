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
struct inode {int i_mode; int i_state; int /*<<< orphan*/  i_mutex; TYPE_1__* i_sb; } ;
struct file_system_type {int /*<<< orphan*/  i_mutex_dir_key; int /*<<< orphan*/  i_mutex_key; } ;
struct TYPE_2__ {struct file_system_type* s_type; } ;

/* Variables and functions */
 int I_LOCK ; 
 int I_NEW ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_match_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up_inode (struct inode*) ; 

void unlock_new_inode(struct inode *inode)
{
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	if (inode->i_mode & S_IFDIR) {
		struct file_system_type *type = inode->i_sb->s_type;

		/* Set new key only if filesystem hasn't already changed it */
		if (!lockdep_match_class(&inode->i_mutex,
		    &type->i_mutex_key)) {
			/*
			 * ensure nobody is actually holding i_mutex
			 */
			mutex_destroy(&inode->i_mutex);
			mutex_init(&inode->i_mutex);
			lockdep_set_class(&inode->i_mutex,
					  &type->i_mutex_dir_key);
		}
	}
#endif
	/*
	 * This is special!  We do not need the spinlock when clearing I_LOCK,
	 * because we're guaranteed that nobody else tries to do anything about
	 * the state of the inode when it is locked, as we just created it (so
	 * there can be no old holders that haven't tested I_LOCK).
	 * However we must emit the memory barrier so that other CPUs reliably
	 * see the clearing of I_LOCK after the other inode initialisation has
	 * completed.
	 */
	smp_mb();
	WARN_ON((inode->i_state & (I_LOCK|I_NEW)) != (I_LOCK|I_NEW));
	inode->i_state &= ~(I_LOCK|I_NEW);
	wake_up_inode(inode);
}