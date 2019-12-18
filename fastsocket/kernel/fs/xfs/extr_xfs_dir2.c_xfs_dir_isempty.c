#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ if_data; } ;
struct TYPE_11__ {TYPE_2__ if_u1; } ;
struct TYPE_9__ {int di_mode; scalar_t__ di_size; } ;
struct TYPE_13__ {TYPE_3__ i_df; TYPE_1__ i_d; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_12__ {int /*<<< orphan*/  count; } ;
struct TYPE_14__ {TYPE_4__ hdr; } ;
typedef  TYPE_6__ xfs_dir2_sf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 scalar_t__ XFS_IFORK_DSIZE (TYPE_5__*) ; 

int
xfs_dir_isempty(
	xfs_inode_t	*dp)
{
	xfs_dir2_sf_t	*sfp;

	ASSERT((dp->i_d.di_mode & S_IFMT) == S_IFDIR);
	if (dp->i_d.di_size == 0)	/* might happen during shutdown. */
		return 1;
	if (dp->i_d.di_size > XFS_IFORK_DSIZE(dp))
		return 0;
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	return !sfp->hdr.count;
}