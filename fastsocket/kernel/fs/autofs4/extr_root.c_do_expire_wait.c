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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs4_del_expiring (struct dentry*) ; 
 int autofs4_expire_wait (struct dentry*) ; 
 struct dentry* autofs4_lookup_expiring (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static int do_expire_wait(struct dentry *dentry)
{
	struct dentry *expiring;

	expiring = autofs4_lookup_expiring(dentry);
	if (!expiring)
		return autofs4_expire_wait(dentry);
	else {
		/*
		 * If we are racing with expire the request might not
		 * be quite complete, but the directory has been removed
		 * so it must have been successful, just wait for it.
		 */
		autofs4_expire_wait(expiring);
		autofs4_del_expiring(expiring);
		dput(expiring);
	}
	return 0;
}