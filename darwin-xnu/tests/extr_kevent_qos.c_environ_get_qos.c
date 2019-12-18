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
typedef  scalar_t__ qos_class_t ;

/* Variables and functions */
 int ENV_VAR_QOS ; 
 int /*<<< orphan*/  T_ASSERT_EQ (char,char,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_LT (unsigned long,unsigned long,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_QUIET ; 
 void* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qos_env ; 
 int /*<<< orphan*/ * qos_name_env ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  wl_function_name ; 

__attribute__((used)) static void
environ_get_qos(qos_class_t qos[], const char *qos_name[], const char **wl_function)
{
	char *qos_str;
	char *qos_end;
	int i;

	for (i = 0; i < ENV_VAR_QOS; i++) {
		qos_str = getenv(qos_env[i]);
		T_QUIET; T_ASSERT_NOTNULL(qos_str, "getenv(%s)", qos_env[i]);

		unsigned long qos_l = strtoul(qos_str, &qos_end, 10);
		T_QUIET; T_ASSERT_EQ(*qos_end, '\0', "getenv(%s) = '%s' should be an "
				"integer", qos_env[i], qos_str);

		T_QUIET; T_ASSERT_LT(qos_l, (unsigned long)100, "getenv(%s) = '%s' should "
				"be less than 100", qos_env[i], qos_str);

		qos[i] = (qos_class_t)qos_l;
		qos_name[i] = getenv(qos_name_env[i]);
		T_QUIET; T_ASSERT_NOTNULL(qos_name[i], "getenv(%s)", qos_name_env[i]);
	}
	*wl_function = getenv(wl_function_name);
	T_QUIET; T_ASSERT_NOTNULL(*wl_function, "getenv(%s)", wl_function_name);
}