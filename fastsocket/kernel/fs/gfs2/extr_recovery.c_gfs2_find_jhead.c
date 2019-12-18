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
typedef  int u32 ;
struct gfs2_log_header_host {scalar_t__ lh_sequence; } ;
struct gfs2_jdesc {int jd_blocks; } ;

/* Variables and functions */
 int find_good_lh (struct gfs2_jdesc*,int*,struct gfs2_log_header_host*) ; 
 int jhead_scan (struct gfs2_jdesc*,struct gfs2_log_header_host*) ; 

int gfs2_find_jhead(struct gfs2_jdesc *jd, struct gfs2_log_header_host *head)
{
	struct gfs2_log_header_host lh_1, lh_m;
	u32 blk_1, blk_2, blk_m;
	int error;

	blk_1 = 0;
	blk_2 = jd->jd_blocks - 1;

	for (;;) {
		blk_m = (blk_1 + blk_2) / 2;

		error = find_good_lh(jd, &blk_1, &lh_1);
		if (error)
			return error;

		error = find_good_lh(jd, &blk_m, &lh_m);
		if (error)
			return error;

		if (blk_1 == blk_m || blk_m == blk_2)
			break;

		if (lh_1.lh_sequence <= lh_m.lh_sequence)
			blk_1 = blk_m;
		else
			blk_2 = blk_m;
	}

	error = jhead_scan(jd, &lh_1);
	if (error)
		return error;

	*head = lh_1;

	return error;
}