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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dt_stat_t ;
typedef  int /*<<< orphan*/  deltas ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,char const*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  dt_stat_add (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  dt_stat_create (char*,char*,char const*) ; 
 int /*<<< orphan*/  dt_stat_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_stat_stable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_if_unsupported () ; 
 int sysctlbyname (char const*,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perf_sysctl_deltas(const char *sysctl_name, const char *stat_name)
{
	uint64_t deltas[2];
	size_t deltas_size;
	int r;

	T_SETUPBEGIN;
	skip_if_unsupported();

	dt_stat_t instrs = dt_stat_create("instructions", "%s_instrs",
			stat_name);
	dt_stat_t cycles = dt_stat_create("cycles", "%s_cycles", stat_name);
	T_SETUPEND;

	while (!dt_stat_stable(instrs) || !dt_stat_stable(cycles)) {
		deltas_size = sizeof(deltas);
		r = sysctlbyname(sysctl_name, deltas, &deltas_size, NULL, 0);
		T_QUIET;
		T_ASSERT_POSIX_SUCCESS(r, "sysctlbyname(\"%s\", ...)", sysctl_name);
		dt_stat_add(instrs, (double)deltas[0]);
		dt_stat_add(cycles, (double)deltas[1]);
	}

	dt_stat_finalize(instrs);
	dt_stat_finalize(cycles);
}