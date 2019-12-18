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
struct proc_dir_entry {unsigned int low_ino; struct proc_dir_entry* data; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int PROC_DYNAMIC_FIRST ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_free_inum (unsigned int) ; 

void free_proc_entry(struct proc_dir_entry *de)
{
	unsigned int ino = de->low_ino;

	if (ino < PROC_DYNAMIC_FIRST)
		return;

	proc_free_inum(ino);

	if (S_ISLNK(de->mode))
		kfree(de->data);
	kfree(de);
}