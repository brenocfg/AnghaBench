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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_process_vm_writev ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec const*,unsigned long,struct iovec const*,unsigned long,unsigned long) ; 

ssize_t process_vm_writev(pid_t pid, const struct iovec *lvec, unsigned long liovcnt, const struct iovec *rvec, unsigned long riovcnt, unsigned long flags)
{
	return syscall(SYS_process_vm_writev, pid, lvec, liovcnt, rvec, riovcnt, flags);
}