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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_splice ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,unsigned int) ; 

ssize_t splice(int fd_in, off_t *off_in, int fd_out, off_t *off_out, size_t len, unsigned flags)
{
	return syscall(SYS_splice, fd_in, off_in, fd_out, off_out, len, flags);
}