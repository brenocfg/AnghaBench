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
struct gfs2_sbd {int /*<<< orphan*/  sd_vfs; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t statfs_sync_store(struct gfs2_sbd *sdp, const char *buf,
				 size_t len)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (simple_strtol(buf, NULL, 0) != 1)
		return -EINVAL;

	gfs2_statfs_sync(sdp->sd_vfs, 0);
	return len;
}