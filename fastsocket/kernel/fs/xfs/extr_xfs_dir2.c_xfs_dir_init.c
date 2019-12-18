#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  t_mountp; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_9__ {int di_mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_ino; TYPE_1__ i_d; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_12__ {TYPE_2__* trans; TYPE_3__* dp; } ;
typedef  TYPE_4__ xfs_da_args_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int xfs_dir2_sf_create (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int xfs_dir_ino_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_dir_init(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	xfs_inode_t	*pdp)
{
	xfs_da_args_t	args;
	int		error;

	memset((char *)&args, 0, sizeof(args));
	args.dp = dp;
	args.trans = tp;
	ASSERT((dp->i_d.di_mode & S_IFMT) == S_IFDIR);
	if ((error = xfs_dir_ino_validate(tp->t_mountp, pdp->i_ino)))
		return error;
	return xfs_dir2_sf_create(&args, pdp->i_ino);
}