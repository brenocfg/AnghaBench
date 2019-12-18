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
struct fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* generic_fh_to_dentry (struct super_block*,struct fid*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_nfs_get_inode ; 

__attribute__((used)) static struct dentry *jffs2_fh_to_dentry(struct super_block *sb, struct fid *fid,
					 int fh_len, int fh_type)
{
        return generic_fh_to_dentry(sb, fid, fh_len, fh_type,
                                    jffs2_nfs_get_inode);
}