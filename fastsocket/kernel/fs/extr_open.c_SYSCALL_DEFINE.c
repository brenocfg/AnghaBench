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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int SYSCALL_DEFINE ;

/* Variables and functions */
 int EBADF ; 
 int do_fallocate (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

SYSCALL_DEFINE(fallocate)(int fd, int mode, loff_t offset, loff_t len)
{
	struct file *file;
	int error = -EBADF;

	file = fget(fd);
	if (file) {
		error = do_fallocate(file, mode, offset, len);
		fput(file);
	}

	return error;
}