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
struct iattr {int ia_valid; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int ATTR_KILL_PRIV ; 
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_change (struct dentry*,struct iattr*) ; 

__attribute__((used)) static void kill_suid(struct dentry *dentry)
{
	struct iattr	ia;
	ia.ia_valid = ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_KILL_PRIV;

	mutex_lock(&dentry->d_inode->i_mutex);
	notify_change(dentry, &ia);
	mutex_unlock(&dentry->d_inode->i_mutex);
}