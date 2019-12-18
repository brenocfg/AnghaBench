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
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct file* exe_file; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct file *get_mm_exe_file(struct mm_struct *mm)
{
	struct file *exe_file;

	/* We need mmap_sem to protect against races with removal of
	 * VM_EXECUTABLE vmas */
	down_read(&mm->mmap_sem);
	exe_file = mm->exe_file;
	if (exe_file)
		get_file(exe_file);
	up_read(&mm->mmap_sem);
	return exe_file;
}