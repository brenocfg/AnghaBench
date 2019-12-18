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
struct xfs_mount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ilf_boffset; int /*<<< orphan*/  ilf_len; int /*<<< orphan*/  ilf_blkno; int /*<<< orphan*/  ilf_ino; int /*<<< orphan*/  ilf_type; } ;
struct xfs_inode_log_item {TYPE_1__ ili_format; int /*<<< orphan*/  ili_item; struct xfs_inode* ili_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  im_boffset; int /*<<< orphan*/  im_len; int /*<<< orphan*/  im_blkno; } ;
struct xfs_inode {TYPE_2__ i_imap; int /*<<< orphan*/  i_ino; struct xfs_inode_log_item* i_itemp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_LI_INODE ; 
 struct xfs_inode_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ili_zone ; 
 int /*<<< orphan*/  xfs_inode_item_ops ; 
 int /*<<< orphan*/  xfs_log_item_init (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_inode_item_init(
	struct xfs_inode	*ip,
	struct xfs_mount	*mp)
{
	struct xfs_inode_log_item *iip;

	ASSERT(ip->i_itemp == NULL);
	iip = ip->i_itemp = kmem_zone_zalloc(xfs_ili_zone, KM_SLEEP);

	iip->ili_inode = ip;
	xfs_log_item_init(mp, &iip->ili_item, XFS_LI_INODE,
						&xfs_inode_item_ops);
	iip->ili_format.ilf_type = XFS_LI_INODE;
	iip->ili_format.ilf_ino = ip->i_ino;
	iip->ili_format.ilf_blkno = ip->i_imap.im_blkno;
	iip->ili_format.ilf_len = ip->i_imap.im_len;
	iip->ili_format.ilf_boffset = ip->i_imap.im_boffset;
}