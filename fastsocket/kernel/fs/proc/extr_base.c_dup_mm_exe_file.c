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
struct mm_struct {int /*<<< orphan*/  exe_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_mm_exe_file (struct mm_struct*) ; 

void dup_mm_exe_file(struct mm_struct *oldmm, struct mm_struct *newmm)
{
	/* It's safe to write the exe_file pointer without exe_file_lock because
	 * this is called during fork when the task is not yet in /proc */
	newmm->exe_file = get_mm_exe_file(oldmm);
}