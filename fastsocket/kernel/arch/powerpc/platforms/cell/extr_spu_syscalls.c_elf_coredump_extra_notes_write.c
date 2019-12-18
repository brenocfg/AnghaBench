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
struct spufs_calls {int (* coredump_extra_notes_write ) (struct file*,int /*<<< orphan*/ *) ;} ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct spufs_calls* spufs_calls_get () ; 
 int /*<<< orphan*/  spufs_calls_put (struct spufs_calls*) ; 
 int stub1 (struct file*,int /*<<< orphan*/ *) ; 

int elf_coredump_extra_notes_write(struct file *file, loff_t *foffset)
{
	struct spufs_calls *calls;
	int ret;

	calls = spufs_calls_get();
	if (!calls)
		return 0;

	ret = calls->coredump_extra_notes_write(file, foffset);

	spufs_calls_put(calls);

	return ret;
}