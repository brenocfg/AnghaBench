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
struct vfsmount {struct mnt_namespace* mnt_ns; int /*<<< orphan*/  mnt_list; int /*<<< orphan*/  mnt_root; } ;
struct mnt_namespace {struct vfsmount* root; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct vfsmount* mnt; } ;
struct TYPE_3__ {struct vfsmount* mnt; } ;
struct fs_struct {TYPE_2__ pwd; TYPE_1__ root; } ;

/* Variables and functions */
 int CL_COPY_ALL ; 
 int CL_EXPIRE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mnt_namespace* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mnt_namespace*) ; 
 struct mnt_namespace* alloc_mnt_ns () ; 
 struct vfsmount* copy_tree (struct vfsmount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mntget (struct vfsmount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  namespace_sem ; 
 struct vfsmount* next_mnt (struct vfsmount*,struct vfsmount*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfsmount_lock ; 

__attribute__((used)) static struct mnt_namespace *dup_mnt_ns(struct mnt_namespace *mnt_ns,
		struct fs_struct *fs)
{
	struct mnt_namespace *new_ns;
	struct vfsmount *rootmnt = NULL, *pwdmnt = NULL;
	struct vfsmount *p, *q;

	new_ns = alloc_mnt_ns();
	if (IS_ERR(new_ns))
		return new_ns;

	down_write(&namespace_sem);
	/* First pass: copy the tree topology */
	new_ns->root = copy_tree(mnt_ns->root, mnt_ns->root->mnt_root,
					CL_COPY_ALL | CL_EXPIRE);
	if (!new_ns->root) {
		up_write(&namespace_sem);
		free_mnt_ns(mnt_ns);
		return ERR_PTR(-ENOMEM);
	}
	spin_lock(&vfsmount_lock);
	list_add_tail(&new_ns->list, &new_ns->root->mnt_list);
	spin_unlock(&vfsmount_lock);

	/*
	 * Second pass: switch the tsk->fs->* elements and mark new vfsmounts
	 * as belonging to new namespace.  We have already acquired a private
	 * fs_struct, so tsk->fs->lock is not needed.
	 */
	p = mnt_ns->root;
	q = new_ns->root;
	while (p) {
		q->mnt_ns = new_ns;
		if (fs) {
			if (p == fs->root.mnt) {
				rootmnt = p;
				fs->root.mnt = mntget(q);
			}
			if (p == fs->pwd.mnt) {
				pwdmnt = p;
				fs->pwd.mnt = mntget(q);
			}
		}
		p = next_mnt(p, mnt_ns->root);
		q = next_mnt(q, new_ns->root);
	}
	up_write(&namespace_sem);

	if (rootmnt)
		mntput(rootmnt);
	if (pwdmnt)
		mntput(pwdmnt);

	return new_ns;
}