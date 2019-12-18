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
 int /*<<< orphan*/  EXEC_PATH_ENVIRONMENT ; 
 int /*<<< orphan*/  PERF_EXEC_PATH ; 
 char const* argv_exec_path ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 char const* system_path (int /*<<< orphan*/ ) ; 

const char *perf_exec_path(void)
{
	const char *env;

	if (argv_exec_path)
		return argv_exec_path;

	env = getenv(EXEC_PATH_ENVIRONMENT);
	if (env && *env) {
		return env;
	}

	return system_path(PERF_EXEC_PATH);
}