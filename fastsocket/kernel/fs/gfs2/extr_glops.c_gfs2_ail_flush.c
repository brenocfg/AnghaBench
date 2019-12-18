#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_log_descriptor {int dummy; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_ail_count; struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gfs2_ail_flush (struct gfs2_glock*,int,unsigned int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

void gfs2_ail_flush(struct gfs2_glock *gl, bool fsync)
{
	struct gfs2_sbd *sdp = gl->gl_sbd;
	unsigned int revokes = atomic_read(&gl->gl_ail_count);
	unsigned int max_revokes = (sdp->sd_sb.sb_bsize - sizeof(struct gfs2_log_descriptor)) / sizeof(u64);
	int ret;

	if (!revokes)
		return;

	while (revokes > max_revokes)
		max_revokes += (sdp->sd_sb.sb_bsize - sizeof(struct gfs2_meta_header)) / sizeof(u64);

	ret = gfs2_trans_begin(sdp, 0, max_revokes);
	if (ret)
		return;
	__gfs2_ail_flush(gl, fsync, max_revokes);
	gfs2_trans_end(sdp);
	gfs2_log_flush(sdp, NULL);
}