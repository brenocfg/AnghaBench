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
struct pid_namespace {int /*<<< orphan*/  last_pid; } ;

/* Variables and functions */
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ pid_before (int,int,int) ; 

__attribute__((used)) static void set_last_pid(struct pid_namespace *pid_ns, int base, int pid)
{
	int prev;
	int last_write = base;
	do {
		prev = last_write;
		last_write = cmpxchg(&pid_ns->last_pid, prev, pid);
	} while ((prev != last_write) && (pid_before(base, last_write, pid)));
}