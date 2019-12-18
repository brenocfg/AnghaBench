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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  lookup_lock; } ;
struct autofs_info {int /*<<< orphan*/  active; int /*<<< orphan*/  active_count; } ;

/* Variables and functions */
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void autofs4_del_active(struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	if (ino) {
		spin_lock(&sbi->lookup_lock);
		ino->active_count--;
		if (!ino->active_count) {
			if (!list_empty(&ino->active))
				list_del_init(&ino->active);
		}
		spin_unlock(&sbi->lookup_lock);
	}
	return;
}