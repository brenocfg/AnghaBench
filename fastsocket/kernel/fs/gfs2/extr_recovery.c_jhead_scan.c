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
struct gfs2_log_header_host {unsigned int lh_blkno; scalar_t__ lh_sequence; } ;
struct gfs2_jdesc {unsigned int jd_blocks; int /*<<< orphan*/  jd_inode; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFS2_I (int /*<<< orphan*/ ) ; 
 int get_log_header (struct gfs2_jdesc*,unsigned int,struct gfs2_log_header_host*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jhead_scan(struct gfs2_jdesc *jd, struct gfs2_log_header_host *head)
{
	unsigned int blk = head->lh_blkno;
	struct gfs2_log_header_host lh;
	int error;

	for (;;) {
		if (++blk == jd->jd_blocks)
			blk = 0;

		error = get_log_header(jd, blk, &lh);
		if (error < 0)
			return error;
		if (error == 1)
			continue;

		if (lh.lh_sequence == head->lh_sequence) {
			gfs2_consist_inode(GFS2_I(jd->jd_inode));
			return -EIO;
		}
		if (lh.lh_sequence < head->lh_sequence)
			break;

		*head = lh;
	}

	return 0;
}