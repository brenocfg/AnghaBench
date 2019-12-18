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
struct TYPE_6__ {struct file* file; } ;
struct TYPE_5__ {TYPE_3__ open; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt; } ;
struct nameidata {TYPE_2__ intent; TYPE_1__ path; } ;
struct file {int dummy; } ;
typedef  struct file dentry ;
struct cred {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 struct file* __dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*,int (*) (struct inode*,struct file*),struct cred const*) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  dget (struct file*) ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_open_intent (struct nameidata*) ; 

struct file *lookup_instantiate_filp(struct nameidata *nd, struct dentry *dentry,
		int (*open)(struct inode *, struct file *))
{
	const struct cred *cred = current_cred();

	if (IS_ERR(nd->intent.open.file))
		goto out;
	if (IS_ERR(dentry))
		goto out_err;
	nd->intent.open.file = __dentry_open(dget(dentry), mntget(nd->path.mnt),
					     nd->intent.open.file,
					     open, cred);
out:
	return nd->intent.open.file;
out_err:
	release_open_intent(nd);
	nd->intent.open.file = (struct file *)dentry;
	goto out;
}