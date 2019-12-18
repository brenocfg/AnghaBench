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
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*,...) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int posix_spawn (int*,char* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,float*,char*) ; 
 char* strstr (char*,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fix_cpu_frequency(void)
{
#if CONFIG_EMBEDDED
	int spawn_ret, pid;
	char *const clpcctrl_args[] = {"/usr/local/bin/clpcctrl", "-f", "5000", NULL};

	T_LOG("Setting cpu frequency to %d\n", 5000);

	spawn_ret = posix_spawn(&pid, clpcctrl_args[0], NULL, NULL, clpcctrl_args, environ);
	waitpid(pid, &spawn_ret, 0);

#else /*CONFIG_EMBEDDED*/

	int spawn_ret, pid;
	int ret, nom_freq;
	size_t len;
	float val;
	char scale;
	char *buffer, *cpu_freq;
	char str_val[10];

	ret = sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
	T_QUIET;T_ASSERT_POSIX_SUCCESS(ret, "sysctlbyname machdep.cpu.brand_string");

	buffer = malloc(len+2);
	ret = sysctlbyname("machdep.cpu.brand_string", buffer, &len, NULL, 0);
	T_QUIET;T_ASSERT_POSIX_SUCCESS(ret, "sysctlbyname machdep.cpu.brand_string");
	buffer[len+1] = '\0';

	cpu_freq = strstr(buffer, "CPU @ ");
	if (cpu_freq == NULL) {
		T_LOG("Could not fix frequency, %s field not present\n", "CPU @ ");
		goto out;
	}

	if (strstr(cpu_freq, "Hz") != NULL) {
		sscanf(cpu_freq, "CPU @ %f%cHz", &val, &scale);
	} else {
		if (strstr(cpu_freq, "hz") != NULL) {
			sscanf(cpu_freq, "CPU @ %f%chz", &val, &scale);
		} else {
			T_LOG("Could not fix frequency, %s field not present\n", "Hz");
			goto out;
		}
	}

	switch(scale){
	case 'M':
	case 'm':
		nom_freq = (int) val;
		break;
	case 'G':
	case 'g':
		nom_freq = (int) (val*1000);
		break;
	default:
		T_LOG("Could not fix frequency, scale field is %c\n", scale);
		goto out;
	}

	snprintf(str_val, 10, "%d", nom_freq);
	T_LOG("Setting min and max cpu frequency to %d (%s)\n", nom_freq, str_val);
	char *xcpm_args[] = {"/usr/local/bin/xcpm", "limits", str_val, str_val, NULL};
	spawn_ret = posix_spawn(&pid, xcpm_args[0], NULL, NULL, xcpm_args, environ);
	waitpid(pid, &spawn_ret, 0);

out:
	free(buffer);
	return;
#endif /*CONFIG_EMBEDDED*/
}