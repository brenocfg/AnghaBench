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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_dirent {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_dirent_find_space ; 
 struct gfs2_dirent* gfs2_dirent_scan (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*,int /*<<< orphan*/ *) ; 
 struct gfs2_dirent* gfs2_init_dirent (struct inode*,struct gfs2_dirent*,struct qstr const*,struct buffer_head*) ; 

__attribute__((used)) static struct gfs2_dirent *gfs2_dirent_alloc(struct inode *inode,
					     struct buffer_head *bh,
					     const struct qstr *name)
{
	struct gfs2_dirent *dent;
	dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
				gfs2_dirent_find_space, name, NULL);
	if (!dent || IS_ERR(dent))
		return dent;
	return gfs2_init_dirent(inode, dent, name, bh);
}