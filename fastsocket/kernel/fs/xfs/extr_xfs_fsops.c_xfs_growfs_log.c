#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_growlock; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_growfs_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xfs_growfs_log_private (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
xfs_growfs_log(
	xfs_mount_t		*mp,
	xfs_growfs_log_t	*in)
{
	int error;

	if (!capable(CAP_SYS_ADMIN))
		return XFS_ERROR(EPERM);
	if (!mutex_trylock(&mp->m_growlock))
		return XFS_ERROR(EWOULDBLOCK);
	error = xfs_growfs_log_private(mp, in);
	mutex_unlock(&mp->m_growlock);
	return error;
}