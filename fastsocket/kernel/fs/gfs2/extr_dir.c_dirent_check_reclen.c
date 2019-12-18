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
typedef  int u16 ;
struct gfs2_inode {int dummy; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dirent_check_reclen(struct gfs2_inode *dip,
			       const struct gfs2_dirent *d, const void *end_p)
{
	const void *ptr = d;
	u16 rec_len = be16_to_cpu(d->de_rec_len);

	if (unlikely(rec_len < sizeof(struct gfs2_dirent)))
		goto broken;
	ptr += rec_len;
	if (ptr < end_p)
		return rec_len;
	if (ptr == end_p)
		return -ENOENT;
broken:
	gfs2_consist_inode(dip);
	return -EIO;
}