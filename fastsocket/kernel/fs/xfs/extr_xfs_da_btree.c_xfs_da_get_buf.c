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
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  int /*<<< orphan*/  xfs_dabuf_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
typedef  int /*<<< orphan*/  inst_t ;

/* Variables and functions */
 scalar_t__ __return_address ; 
 int xfs_da_do_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xfs_da_get_buf(
	xfs_trans_t	*trans,
	xfs_inode_t	*dp,
	xfs_dablk_t	bno,
	xfs_daddr_t		mappedbno,
	xfs_dabuf_t	**bpp,
	int		whichfork)
{
	return xfs_da_do_buf(trans, dp, bno, &mappedbno, bpp, whichfork, 0,
						 (inst_t *)__return_address);
}