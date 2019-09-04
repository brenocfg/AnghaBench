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
struct rusage {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_wait4 ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct rusage*) ; 

pid_t wait4(pid_t pid, int *status, int options, struct rusage *usage)
{
	return syscall(SYS_wait4, pid, status, options, usage);
}