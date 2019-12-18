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
typedef  scalar_t__ xfs_extlen_t ;
struct TYPE_4__ {int di_flags; scalar_t__ di_extsize; } ;
struct xfs_inode {TYPE_3__* i_mount; TYPE_1__ i_d; } ;
struct TYPE_5__ {scalar_t__ sb_rextsize; } ;
struct TYPE_6__ {TYPE_2__ m_sb; } ;

/* Variables and functions */
 int XFS_DIFLAG_EXTSIZE ; 
 scalar_t__ XFS_IS_REALTIME_INODE (struct xfs_inode*) ; 

xfs_extlen_t
xfs_get_extsz_hint(
	struct xfs_inode	*ip)
{
	if ((ip->i_d.di_flags & XFS_DIFLAG_EXTSIZE) && ip->i_d.di_extsize)
		return ip->i_d.di_extsize;
	if (XFS_IS_REALTIME_INODE(ip))
		return ip->i_mount->m_sb.sb_rextsize;
	return 0;
}