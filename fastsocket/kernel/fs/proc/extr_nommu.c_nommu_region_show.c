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
struct vm_region {int vm_flags; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct file* vm_file; } ;
struct seq_file {int dummy; } ;
struct inode {unsigned long i_ino; TYPE_2__* i_sb; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYSHARE ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  seq_path (struct seq_file*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int nommu_region_show(struct seq_file *m, struct vm_region *region)
{
	unsigned long ino = 0;
	struct file *file;
	dev_t dev = 0;
	int flags, len;

	flags = region->vm_flags;
	file = region->vm_file;

	if (file) {
		struct inode *inode = region->vm_file->f_path.dentry->d_inode;
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
	}

	seq_printf(m,
		   "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu %n",
		   region->vm_start,
		   region->vm_end,
		   flags & VM_READ ? 'r' : '-',
		   flags & VM_WRITE ? 'w' : '-',
		   flags & VM_EXEC ? 'x' : '-',
		   flags & VM_MAYSHARE ? flags & VM_SHARED ? 'S' : 's' : 'p',
		   ((loff_t)region->vm_pgoff) << PAGE_SHIFT,
		   MAJOR(dev), MINOR(dev), ino, &len);

	if (file) {
		len = 25 + sizeof(void *) * 6 - len;
		if (len < 1)
			len = 1;
		seq_printf(m, "%*c", len, ' ');
		seq_path(m, &file->f_path, "");
	}

	seq_putc(m, '\n');
	return 0;
}