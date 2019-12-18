#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i_ino; int /*<<< orphan*/ * i_gdquot; int /*<<< orphan*/ * i_udquot; TYPE_1__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_7__ {scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; } ;
struct TYPE_6__ {TYPE_2__ m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  trace_xfs_dquot_dqdetach (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_qm_dqrele (int /*<<< orphan*/ *) ; 

void
xfs_qm_dqdetach(
	xfs_inode_t	*ip)
{
	if (!(ip->i_udquot || ip->i_gdquot))
		return;

	trace_xfs_dquot_dqdetach(ip);

	ASSERT(ip->i_ino != ip->i_mount->m_sb.sb_uquotino);
	ASSERT(ip->i_ino != ip->i_mount->m_sb.sb_gquotino);
	if (ip->i_udquot) {
		xfs_qm_dqrele(ip->i_udquot);
		ip->i_udquot = NULL;
	}
	if (ip->i_gdquot) {
		xfs_qm_dqrele(ip->i_gdquot);
		ip->i_gdquot = NULL;
	}
}