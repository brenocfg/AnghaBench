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
struct super_block {int dummy; } ;
struct fid {int /*<<< orphan*/ * raw; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* reiserfs_get_dentry (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dentry *reiserfs_fh_to_parent(struct super_block *sb, struct fid *fid,
		int fh_len, int fh_type)
{
	if (fh_type < 4)
		return NULL;

	return reiserfs_get_dentry(sb,
		(fh_type >= 5) ? fid->raw[3] : fid->raw[2],
		(fh_type >= 5) ? fid->raw[4] : fid->raw[3],
		(fh_type == 6) ? fid->raw[5] : 0);
}