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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * slow_work_pids ; 

__attribute__((used)) static inline void slow_work_set_thread_pid(int id, pid_t pid)
{
#ifdef CONFIG_SLOW_WORK_DEBUG
	slow_work_pids[id] = pid;
#endif
}