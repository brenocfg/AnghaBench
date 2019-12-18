#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_mapping; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int loff_t ;
struct TYPE_9__ {scalar_t__ time; int /*<<< orphan*/  clientCanCacheRead; } ;
struct TYPE_8__ {scalar_t__ nrpages; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_5__* CIFS_I (struct inode*) ; 
 int SEEK_END ; 
 int cifs_revalidate_file_attr (struct file*) ; 
 int filemap_fdatawait (TYPE_3__*) ; 
 int generic_file_llseek_unlocked (struct file*,int,int) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_3__*,int) ; 

__attribute__((used)) static loff_t cifs_llseek(struct file *file, loff_t offset, int origin)
{
	/* origin == SEEK_END => we must revalidate the cached file length */
	if (origin == SEEK_END) {
		int rc;
		struct inode *inode = file->f_path.dentry->d_inode;

		/*
		 * We need to be sure that all dirty pages are written and the
		 * server has the newest file length.
		 */
		if (!CIFS_I(inode)->clientCanCacheRead && inode->i_mapping &&
		    inode->i_mapping->nrpages != 0) {
			rc = filemap_fdatawait(inode->i_mapping);
			if (rc) {
				mapping_set_error(inode->i_mapping, rc);
				return rc;
			}
		}
		/*
		 * Some applications poll for the file length in this strange
		 * way so we must seek to end on non-oplocked files by
		 * setting the revalidate time to zero.
		 */
		CIFS_I(inode)->time = 0;

		rc = cifs_revalidate_file_attr(file);
		if (rc < 0)
			return (loff_t)rc;
	}
	return generic_file_llseek_unlocked(file, offset, origin);
}