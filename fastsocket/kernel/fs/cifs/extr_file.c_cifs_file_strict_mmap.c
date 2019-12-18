#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  clientCanCacheRead; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_3__* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int cifs_invalidate_mapping (struct inode*) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 

int cifs_file_strict_mmap(struct file *file, struct vm_area_struct *vma)
{
	int rc, xid;
	struct inode *inode = file->f_path.dentry->d_inode;

	xid = GetXid();

	if (!CIFS_I(inode)->clientCanCacheRead) {
		rc = cifs_invalidate_mapping(inode);
		if (rc)
			return rc;
	}

	rc = generic_file_mmap(file, vma);
	FreeXid(xid);
	return rc;
}