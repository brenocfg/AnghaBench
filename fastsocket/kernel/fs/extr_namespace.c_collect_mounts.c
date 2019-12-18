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
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int CL_COPY_ALL ; 
 int CL_PRIVATE ; 
 struct vfsmount* copy_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct vfsmount *collect_mounts(struct path *path)
{
	struct vfsmount *tree;
	down_write(&namespace_sem);
	tree = copy_tree(path->mnt, path->dentry, CL_COPY_ALL | CL_PRIVATE);
	up_write(&namespace_sem);
	return tree;
}