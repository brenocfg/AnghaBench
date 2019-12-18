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
struct file {int f_flags; int /*<<< orphan*/  f_path; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {scalar_t__ in_execve; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_TRUNC ; 
 TYPE_1__* current ; 
 int tomoyo_check_open_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tomoyo_domain () ; 

__attribute__((used)) static int tomoyo_dentry_open(struct file *f, const struct cred *cred)
{
	int flags = f->f_flags;

	if ((flags + 1) & O_ACCMODE)
		flags++;
	flags |= f->f_flags & (O_APPEND | O_TRUNC);
	/* Don't check read permission here if called from do_execve(). */
	if (current->in_execve)
		return 0;
	return tomoyo_check_open_permission(tomoyo_domain(), &f->f_path, flags);
}