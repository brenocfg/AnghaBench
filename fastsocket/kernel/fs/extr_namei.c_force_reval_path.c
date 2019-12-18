#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {struct dentry* dentry; } ;
struct nameidata {int dummy; } ;
struct dentry {TYPE_3__* d_op; TYPE_2__* d_sb; } ;
struct TYPE_6__ {int (* d_revalidate ) (struct dentry*,struct nameidata*) ;} ;
struct TYPE_5__ {TYPE_1__* s_type; } ;
struct TYPE_4__ {int fs_flags; } ;

/* Variables and functions */
 int ESTALE ; 
 int FS_REVAL_DOT ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 int stub1 (struct dentry*,struct nameidata*) ; 

__attribute__((used)) static int
force_reval_path(struct path *path, struct nameidata *nd)
{
	int status;
	struct dentry *dentry = path->dentry;

	/*
	 * only check on filesystems where it's possible for the dentry to
	 * become stale. It's assumed that if this flag is set then the
	 * d_revalidate op will also be defined.
	 */
	if (!(dentry->d_sb->s_type->fs_flags & FS_REVAL_DOT))
		return 0;

	status = dentry->d_op->d_revalidate(dentry, nd);
	if (status > 0)
		return 0;

	if (!status) {
		d_invalidate(dentry);
		status = -ESTALE;
	}
	return status;
}