#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  pipe_pid; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  SYS_wait4 ; 
 int __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __syscall_ret (int) ; 
 int /*<<< orphan*/  fclose (TYPE_1__*) ; 

int pclose(FILE *f)
{
	int status, r;
	pid_t pid = f->pipe_pid;
	fclose(f);
	while ((r=__syscall(SYS_wait4, pid, &status, 0, 0)) == -EINTR);
	if (r<0) return __syscall_ret(r);
	return status;
}