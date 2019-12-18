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

/* Variables and functions */
 scalar_t__ compat_ptr (unsigned long) ; 
 int sys_ioctl (unsigned int,unsigned int,unsigned long) ; 

__attribute__((used)) static int do_ioctl32_pointer(unsigned int fd, unsigned int cmd,
			      unsigned long arg, struct file *f)
{
	return sys_ioctl(fd, cmd, (unsigned long)compat_ptr(arg));
}