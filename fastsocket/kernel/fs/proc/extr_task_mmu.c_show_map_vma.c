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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_prev; scalar_t__ vm_pgoff; struct file* vm_file; struct mm_struct* vm_mm; } ;
struct seq_file {int dummy; } ;
struct mm_struct {unsigned long start_brk; unsigned long brk; unsigned long start_stack; } ;
struct inode {unsigned long i_ino; TYPE_2__* i_sb; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
typedef  unsigned long long loff_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 unsigned long long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_EXEC ; 
 int VM_GROWSDOWN ; 
 int VM_MAYSHARE ; 
 int VM_READ ; 
 int VM_WRITE ; 
 char* arch_vma_name (struct vm_area_struct*) ; 
 int /*<<< orphan*/  pad_len_spaces (struct seq_file*,int) ; 
 int /*<<< orphan*/  seq_path (struct seq_file*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,unsigned long,char,char,char,char,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const*) ; 
 int /*<<< orphan*/  vma_stack_continue (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void show_map_vma(struct seq_file *m, struct vm_area_struct *vma)
{
	struct mm_struct *mm = vma->vm_mm;
	struct file *file = vma->vm_file;
	int flags = vma->vm_flags;
	unsigned long ino = 0;
	unsigned long long pgoff = 0;
	unsigned long start;
	dev_t dev = 0;
	int len;

	if (file) {
		struct inode *inode = vma->vm_file->f_path.dentry->d_inode;
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = ((loff_t)vma->vm_pgoff) << PAGE_SHIFT;
	}

	/* We don't show the stack guard page in /proc/maps */
	start = vma->vm_start;
	if (vma->vm_flags & VM_GROWSDOWN)
		if (!vma_stack_continue(vma->vm_prev, vma->vm_start))
			start += PAGE_SIZE;

	seq_printf(m, "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu %n",
			start,
			vma->vm_end,
			flags & VM_READ ? 'r' : '-',
			flags & VM_WRITE ? 'w' : '-',
			flags & VM_EXEC ? 'x' : '-',
			flags & VM_MAYSHARE ? 's' : 'p',
			pgoff,
			MAJOR(dev), MINOR(dev), ino, &len);

	/*
	 * Print the dentry name for named mappings, and a
	 * special [heap] marker for the heap:
	 */
	if (file) {
		pad_len_spaces(m, len);
		seq_path(m, &file->f_path, "\n");
	} else {
		const char *name = arch_vma_name(vma);
		if (!name) {
			if (mm) {
				if (vma->vm_start <= mm->start_brk &&
						vma->vm_end >= mm->brk) {
					name = "[heap]";
				} else if (vma->vm_start <= mm->start_stack &&
					   vma->vm_end >= mm->start_stack) {
					name = "[stack]";
				}
			} else {
				name = "[vdso]";
			}
		}
		if (name) {
			pad_len_spaces(m, len);
			seq_puts(m, name);
		}
	}
	seq_putc(m, '\n');
}