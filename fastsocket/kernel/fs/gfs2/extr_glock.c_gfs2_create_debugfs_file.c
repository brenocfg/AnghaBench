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
struct gfs2_sbd {void* debugfs_dentry_sbstats; int /*<<< orphan*/  debugfs_dir; void* debugfs_dentry_glstats; void* debugfs_dentry_glocks; int /*<<< orphan*/  sd_table_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_delete_debugfs_file (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_glocks_fops ; 
 int /*<<< orphan*/  gfs2_glstats_fops ; 
 int /*<<< orphan*/  gfs2_root ; 
 int /*<<< orphan*/  gfs2_sbstats_fops ; 

int gfs2_create_debugfs_file(struct gfs2_sbd *sdp)
{
	sdp->debugfs_dir = debugfs_create_dir(sdp->sd_table_name, gfs2_root);
	if (!sdp->debugfs_dir)
		return -ENOMEM;
	sdp->debugfs_dentry_glocks = debugfs_create_file("glocks",
							 S_IFREG | S_IRUGO,
							 sdp->debugfs_dir, sdp,
							 &gfs2_glocks_fops);
	if (!sdp->debugfs_dentry_glocks)
		goto fail;

	sdp->debugfs_dentry_glstats = debugfs_create_file("glstats",
							S_IFREG | S_IRUGO,
							sdp->debugfs_dir, sdp,
							&gfs2_glstats_fops);
	if (!sdp->debugfs_dentry_glstats)
		goto fail;

	sdp->debugfs_dentry_sbstats = debugfs_create_file("sbstats",
							S_IFREG | S_IRUGO,
							sdp->debugfs_dir, sdp,
							&gfs2_sbstats_fops);
	if (!sdp->debugfs_dentry_sbstats)
		goto fail;

	return 0;
fail:
	gfs2_delete_debugfs_file(sdp);
	return -ENOMEM;
}