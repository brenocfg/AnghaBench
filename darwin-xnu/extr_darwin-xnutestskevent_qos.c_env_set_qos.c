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
typedef  char const* qos_class_t ;

/* Variables and functions */
 int ENV_VAR_QOS ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * qos_env ; 
 int /*<<< orphan*/ * qos_name_env ; 
 int /*<<< orphan*/  wl_function_name ; 

__attribute__((used)) static void
env_set_qos(char **env, qos_class_t qos[], const char *qos_name[], const char *wl_function)
{
	int i;
	char *qos_str, *qos_name_str;
	for (i = 0; i < ENV_VAR_QOS; i++) {
		T_QUIET; T_ASSERT_POSIX_SUCCESS(asprintf(&qos_str, "%s=%d", qos_env[i] , qos[i]),
			NULL);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(
			asprintf(&qos_name_str, "%s=%s", qos_name_env[i], qos_name[i]), NULL);
		env[2 * i] = qos_str;
		env[2 * i + 1] = qos_name_str;
	}
	T_QUIET; T_ASSERT_POSIX_SUCCESS(asprintf(&env[2 * i], "%s=%s", wl_function_name, wl_function),
			NULL);
	env[2 * i + 1] = NULL;
}