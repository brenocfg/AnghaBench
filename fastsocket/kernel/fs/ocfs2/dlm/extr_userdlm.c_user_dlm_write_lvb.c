#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* lvb; } ;
struct user_lock_res {scalar_t__ l_level; int /*<<< orphan*/  l_lock; TYPE_1__ l_lksb; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {struct user_lock_res ip_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* DLMFS_I (struct inode*) ; 
 unsigned int DLM_LVB_LEN ; 
 scalar_t__ LKM_EXMODE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void user_dlm_write_lvb(struct inode *inode,
			const char *val,
			unsigned int len)
{
	struct user_lock_res *lockres = &DLMFS_I(inode)->ip_lockres;
	char *lvb = lockres->l_lksb.lvb;

	BUG_ON(len > DLM_LVB_LEN);

	spin_lock(&lockres->l_lock);

	BUG_ON(lockres->l_level < LKM_EXMODE);
	memcpy(lvb, val, len);

	spin_unlock(&lockres->l_lock);
}