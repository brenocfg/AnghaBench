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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct gfs2_sbd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_sync_fs(struct super_block *sb, int wait)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	if (wait && sdp)
		gfs2_log_flush(sdp, NULL);
	return 0;
}