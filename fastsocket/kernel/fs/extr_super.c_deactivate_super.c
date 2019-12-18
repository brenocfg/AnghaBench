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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_active; struct file_system_type* s_type; } ;
struct file_system_type {int /*<<< orphan*/  (* kill_sb ) (struct super_block*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 int /*<<< orphan*/  put_super (struct super_block*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int /*<<< orphan*/  vfs_dq_off (struct super_block*,int /*<<< orphan*/ ) ; 

void deactivate_super(struct super_block *s)
{
	struct file_system_type *fs = s->s_type;
	if (atomic_dec_and_test(&s->s_active)) {
		vfs_dq_off(s, 0);
		down_write(&s->s_umount);
		fs->kill_sb(s);
		put_filesystem(fs);
		put_super(s);
	}
}