#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int smb_revalidate_inode (struct dentry*) ; 

__attribute__((used)) static int
smb_file_mmap(struct file * file, struct vm_area_struct * vma)
{
	struct dentry * dentry = file->f_path.dentry;
	int	status;

	VERBOSE("file %s/%s, address %lu - %lu\n",
		DENTRY_PATH(dentry), vma->vm_start, vma->vm_end);

	status = smb_revalidate_inode(dentry);
	if (status) {
		PARANOIA("%s/%s validation failed, error=%d\n",
			 DENTRY_PATH(dentry), status);
		goto out;
	}
	status = generic_file_mmap(file, vma);
out:
	return status;
}