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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sched__get_first_possible_cpu(pid_t pid, cpu_set_t *maskp)
{
	int i, cpu = -1, nrcpus = 1024;
realloc:
	CPU_ZERO(maskp);

	if (sched_getaffinity(pid, sizeof(*maskp), maskp) == -1) {
		if (errno == EINVAL && nrcpus < (1024 << 8)) {
			nrcpus = nrcpus << 2;
			goto realloc;
		}
		perror("sched_getaffinity");
			return -1;
	}

	for (i = 0; i < nrcpus; i++) {
		if (CPU_ISSET(i, maskp)) {
			if (cpu == -1)
				cpu = i;
			else
				CPU_CLR(i, maskp);
		}
	}

	return cpu;
}