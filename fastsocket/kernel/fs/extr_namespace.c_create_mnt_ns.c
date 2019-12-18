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
struct vfsmount {int /*<<< orphan*/  mnt_list; struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {struct vfsmount* root; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct mnt_namespace*) ; 
 struct mnt_namespace* alloc_mnt_ns () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct mnt_namespace *create_mnt_ns(struct vfsmount *mnt)
{
	struct mnt_namespace *new_ns;

	new_ns = alloc_mnt_ns();
	if (!IS_ERR(new_ns)) {
		mnt->mnt_ns = new_ns;
		new_ns->root = mnt;
		list_add(&new_ns->list, &new_ns->root->mnt_list);
	}
	return new_ns;
}