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
struct file {unsigned long f_flags; } ;

/* Variables and functions */
 unsigned int F_SETFL ; 
 unsigned long O_APPEND ; 
 int tomoyo_check_rewrite_permission (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  tomoyo_domain () ; 

__attribute__((used)) static int tomoyo_file_fcntl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	if (cmd == F_SETFL && ((arg ^ file->f_flags) & O_APPEND))
		return tomoyo_check_rewrite_permission(tomoyo_domain(), file);
	return 0;
}