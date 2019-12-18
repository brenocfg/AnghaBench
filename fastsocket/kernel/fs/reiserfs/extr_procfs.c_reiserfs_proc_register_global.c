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
struct proc_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  read_proc_t ;

/* Variables and functions */

struct proc_dir_entry *reiserfs_proc_register_global(char *name,
						     read_proc_t * func)
{
	return NULL;
}