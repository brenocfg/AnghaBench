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
typedef  int /*<<< orphan*/  qos_class_t ;
typedef  int /*<<< orphan*/  dt_helper_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_VAR_FUNCTION ; 
 int ENV_VAR_QOS ; 
 int /*<<< orphan*/  HELPER_TIMEOUT_SECS ; 
 int /*<<< orphan*/  dt_fork_helper (char const*) ; 
 int /*<<< orphan*/  dt_launchd_helper_env (char*,char const*,char**) ; 
 int /*<<< orphan*/  dt_run_helpers (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_set_qos (char**,int /*<<< orphan*/ *,char const**,char const*) ; 
 int /*<<< orphan*/ * g_expected_qos ; 
 char const** g_expected_qos_name ; 

__attribute__((used)) static void
run_client_server(const char *server_name, const char *client_name, qos_class_t qos[],
		const char *qos_name[], const char *wl_function)
{
	char *env[2 * ENV_VAR_QOS + ENV_VAR_FUNCTION + 1];
	env_set_qos(env, qos, qos_name, wl_function);

	for (int i = 0; i < ENV_VAR_QOS; i++) {
		g_expected_qos[i] = qos[i];
		g_expected_qos_name[i] = qos_name[i];
	}

	dt_helper_t helpers[] = {
		dt_launchd_helper_env("com.apple.xnu.test.kevent_qos.plist",
				server_name, env),
		dt_fork_helper(client_name)
	};
	dt_run_helpers(helpers, 2, HELPER_TIMEOUT_SECS);
}