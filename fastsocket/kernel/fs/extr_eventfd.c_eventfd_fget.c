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
struct file {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventfd_fops ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

struct file *eventfd_fget(int fd)
{
	struct file *file;

	file = fget(fd);
	if (!file)
		return ERR_PTR(-EBADF);
	if (file->f_op != &eventfd_fops) {
		fput(file);
		return ERR_PTR(-EINVAL);
	}

	return file;
}