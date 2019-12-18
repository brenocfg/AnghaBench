#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct TYPE_2__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  RES_DINODE ; 
 int __gfs2_setattr_simple (struct inode*,struct iattr*) ; 
 TYPE_1__* current ; 
 int gfs2_trans_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (int /*<<< orphan*/ ) ; 

int gfs2_setattr_simple(struct inode *inode, struct iattr *attr)
{
	int error;

	if (current->journal_info)
		return __gfs2_setattr_simple(inode, attr);

	error = gfs2_trans_begin(GFS2_SB(inode), RES_DINODE, 0);
	if (error)
		return error;

	error = __gfs2_setattr_simple(inode, attr);
	gfs2_trans_end(GFS2_SB(inode));
	return error;
}