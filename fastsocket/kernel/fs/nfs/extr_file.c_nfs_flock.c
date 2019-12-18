#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file_lock {scalar_t__ fl_type; int fl_flags; int /*<<< orphan*/  fl_end; scalar_t__ fl_start; scalar_t__ fl_owner; } ;
struct TYPE_13__ {TYPE_5__* dentry; } ;
struct file {TYPE_6__ f_path; TYPE_1__* f_mapping; } ;
typedef  scalar_t__ fl_owner_t ;
struct TYPE_14__ {int flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {TYPE_4__ d_name; TYPE_3__* d_parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_2__ d_name; } ;
struct TYPE_8__ {struct inode* host; } ;

/* Variables and functions */
 int ENOLCK ; 
 int FL_FLOCK ; 
 scalar_t__ F_UNLCK ; 
 int NFS_MOUNT_LOCAL_FLOCK ; 
 TYPE_7__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 int do_setlk (struct file*,int,struct file_lock*,int) ; 
 int do_unlk (struct file*,int,struct file_lock*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int nfs_flock(struct file *filp, int cmd, struct file_lock *fl)
{
	struct inode *inode = filp->f_mapping->host;
	int is_local = 0;

	dprintk("NFS: flock(%s/%s, t=%x, fl=%x)\n",
			filp->f_path.dentry->d_parent->d_name.name,
			filp->f_path.dentry->d_name.name,
			fl->fl_type, fl->fl_flags);

	if (!(fl->fl_flags & FL_FLOCK))
		return -ENOLCK;

	if (NFS_SERVER(inode)->flags & NFS_MOUNT_LOCAL_FLOCK)
		is_local = 1;

	/* We're simulating flock() locks using posix locks on the server */
	fl->fl_owner = (fl_owner_t)filp;
	fl->fl_start = 0;
	fl->fl_end = OFFSET_MAX;

	if (fl->fl_type == F_UNLCK)
		return do_unlk(filp, cmd, fl, is_local);
	return do_setlk(filp, cmd, fl, is_local);
}