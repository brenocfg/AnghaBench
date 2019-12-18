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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ima_delete_rules () ; 
 int /*<<< orphan*/ * ima_policy ; 
 int /*<<< orphan*/  ima_update_policy () ; 
 int /*<<< orphan*/  policy_opencount ; 
 int /*<<< orphan*/  securityfs_remove (int /*<<< orphan*/ *) ; 
 int valid_policy ; 

__attribute__((used)) static int ima_release_policy(struct inode *inode, struct file *file)
{
	if (!valid_policy) {
		ima_delete_rules();
		valid_policy = 1;
		atomic_set(&policy_opencount, 1);
		return 0;
	}
	ima_update_policy();
	securityfs_remove(ima_policy);
	ima_policy = NULL;
	return 0;
}