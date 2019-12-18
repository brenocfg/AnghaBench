#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mru_cache_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; TYPE_1__* i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_4__ {int /*<<< orphan*/ * m_filestream; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_mru_cache_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
xfs_filestream_deassociate(
	xfs_inode_t	*ip)
{
	xfs_mru_cache_t	*cache = ip->i_mount->m_filestream;

	xfs_mru_cache_delete(cache, ip->i_ino);
}