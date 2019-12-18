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
struct gfs2_sbd {struct super_block* sd_vfs; int /*<<< orphan*/  sd_tune; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long gfs2_tune_get_i (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  quotad_error (struct gfs2_sbd*,char const*,int) ; 

__attribute__((used)) static void quotad_check_timeo(struct gfs2_sbd *sdp, const char *msg,
			       int (*fxn)(struct super_block *sb, int type),
			       unsigned long t, unsigned long *timeo,
			       unsigned int *new_timeo)
{
	if (t >= *timeo) {
		int error = fxn(sdp->sd_vfs, 0);
		quotad_error(sdp, msg, error);
		*timeo = gfs2_tune_get_i(&sdp->sd_tune, new_timeo) * HZ;
	} else {
		*timeo -= t;
	}
}