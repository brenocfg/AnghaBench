#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  m_filestream; } ;
typedef  TYPE_1__ xfs_mount_t ;

/* Variables and functions */
 int xfs_fstrm_centisecs ; 
 int /*<<< orphan*/  xfs_fstrm_free_func ; 
 int xfs_mru_cache_create (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int
xfs_filestream_mount(
	xfs_mount_t	*mp)
{
	int		err;
	unsigned int	lifetime, grp_count;

	/*
	 * The filestream timer tunable is currently fixed within the range of
	 * one second to four minutes, with five seconds being the default.  The
	 * group count is somewhat arbitrary, but it'd be nice to adhere to the
	 * timer tunable to within about 10 percent.  This requires at least 10
	 * groups.
	 */
	lifetime  = xfs_fstrm_centisecs * 10;
	grp_count = 10;

	err = xfs_mru_cache_create(&mp->m_filestream, lifetime, grp_count,
	                     xfs_fstrm_free_func);

	return err;
}