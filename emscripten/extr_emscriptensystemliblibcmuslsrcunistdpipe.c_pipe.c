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

/* Variables and functions */
 int /*<<< orphan*/  SYS_pipe2 ; 
 int syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int pipe(int fd[2])
{
#ifdef SYS_pipe
	return syscall(SYS_pipe, fd);
#else
	return syscall(SYS_pipe2, fd, 0);
#endif
}