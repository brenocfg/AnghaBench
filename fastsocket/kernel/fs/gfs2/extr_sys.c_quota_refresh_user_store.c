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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int gfs2_quota_refresh (struct gfs2_sbd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t quota_refresh_user_store(struct gfs2_sbd *sdp, const char *buf,
					size_t len)
{
	int error;
	u32 id;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	id = simple_strtoul(buf, NULL, 0);

	error = gfs2_quota_refresh(sdp, 1, id);
	return error ? error : len;
}