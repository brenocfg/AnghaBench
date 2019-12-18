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
struct task_struct {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_FORCE ; 
 int /*<<< orphan*/  host_supports_tls ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int load_TLS (int /*<<< orphan*/ ,struct task_struct*) ; 

int arch_switch_tls(struct task_struct *to)
{
	if (!host_supports_tls)
		return 0;

	/*
	 * We have no need whatsoever to switch TLS for kernel threads; beyond
	 * that, that would also result in us calling os_set_thread_area with
	 * userspace_pid[cpu] == 0, which gives an error.
	 */
	if (likely(to->mm))
		return load_TLS(O_FORCE, to);

	return 0;
}