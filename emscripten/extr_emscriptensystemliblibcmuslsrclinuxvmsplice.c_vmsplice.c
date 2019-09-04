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
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_vmsplice ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,struct iovec const*,size_t,unsigned int) ; 

ssize_t vmsplice(int fd, const struct iovec *iov, size_t cnt, unsigned flags)
{
	return syscall(SYS_vmsplice, fd, iov, cnt, flags);
}