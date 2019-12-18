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
struct inode {int i_mode; scalar_t__ i_uid; int /*<<< orphan*/  i_gid; } ;
struct TYPE_6__ {int i_mode; scalar_t__ i_uid; int /*<<< orphan*/  i_gid; } ;
struct gfs2_inode {TYPE_3__ i_inode; } ;
struct TYPE_4__ {scalar_t__ ar_suiddir; } ;
struct TYPE_5__ {TYPE_1__ sd_args; } ;

/* Variables and functions */
 TYPE_2__* GFS2_SB (TYPE_3__*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 scalar_t__ current_fsuid () ; 

__attribute__((used)) static void munge_mode_uid_gid(const struct gfs2_inode *dip,
			       struct inode *inode)
{
	if (GFS2_SB(&dip->i_inode)->sd_args.ar_suiddir &&
	    (dip->i_inode.i_mode & S_ISUID) && dip->i_inode.i_uid) {
		if (S_ISDIR(inode->i_mode))
			inode->i_mode |= S_ISUID;
		else if (dip->i_inode.i_uid != current_fsuid())
			inode->i_mode &= ~07111;
		inode->i_uid = dip->i_inode.i_uid;
	} else
		inode->i_uid = current_fsuid();

	if (dip->i_inode.i_mode & S_ISGID) {
		if (S_ISDIR(inode->i_mode))
			inode->i_mode |= S_ISGID;
		inode->i_gid = dip->i_inode.i_gid;
	} else
		inode->i_gid = current_fsgid();
}