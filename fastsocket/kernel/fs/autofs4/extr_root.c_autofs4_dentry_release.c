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
struct autofs_info {int /*<<< orphan*/  expiring; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs4_free_ino (struct autofs_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void autofs4_dentry_release(struct dentry *de)
{
	struct autofs_info *inf;

	DPRINTK("releasing %p", de);

	inf = autofs4_dentry_ino(de);
	if (inf) {
		struct autofs_sb_info *sbi = autofs4_sbi(de->d_sb);
		if (sbi) {
			spin_lock(&sbi->lookup_lock);
			if (!list_empty(&inf->active))
				list_del(&inf->active);
			if (!list_empty(&inf->expiring))
				list_del(&inf->expiring);
			spin_unlock(&sbi->lookup_lock);
		}
		autofs4_free_ino(inf);
	}
}