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
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct nameidata {TYPE_2__ path; } ;
struct audit_parent {int /*<<< orphan*/  wdata; scalar_t__ flags; int /*<<< orphan*/  watches; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_IN_WATCH ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct audit_parent* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_free_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_ih ; 
 int /*<<< orphan*/  get_inotify_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inotify_add_watch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_init_watch (int /*<<< orphan*/ *) ; 
 struct audit_parent* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct audit_parent *audit_init_parent(struct nameidata *ndp)
{
	struct audit_parent *parent;
	s32 wd;

	parent = kzalloc(sizeof(*parent), GFP_KERNEL);
	if (unlikely(!parent))
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&parent->watches);
	parent->flags = 0;

	inotify_init_watch(&parent->wdata);
	/* grab a ref so inotify watch hangs around until we take audit_filter_mutex */
	get_inotify_watch(&parent->wdata);
	wd = inotify_add_watch(audit_ih, &parent->wdata,
			       ndp->path.dentry->d_inode, AUDIT_IN_WATCH);
	if (wd < 0) {
		audit_free_parent(&parent->wdata);
		return ERR_PTR(wd);
	}

	return parent;
}