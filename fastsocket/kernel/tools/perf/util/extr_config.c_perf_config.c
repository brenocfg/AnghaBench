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
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 char* config_exclusive_filename ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  mkpath (char*,char const*) ; 
 int perf_config_from_file (int /*<<< orphan*/ ,char*,void*) ; 
 scalar_t__ perf_config_global () ; 
 scalar_t__ perf_config_system () ; 
 char* perf_etc_perfconfig () ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

int perf_config(config_fn_t fn, void *data)
{
	int ret = 0, found = 0;
	const char *home = NULL;

	/* Setting $PERF_CONFIG makes perf read _only_ the given config file. */
	if (config_exclusive_filename)
		return perf_config_from_file(fn, config_exclusive_filename, data);
	if (perf_config_system() && !access(perf_etc_perfconfig(), R_OK)) {
		ret += perf_config_from_file(fn, perf_etc_perfconfig(),
					    data);
		found += 1;
	}

	home = getenv("HOME");
	if (perf_config_global() && home) {
		char *user_config = strdup(mkpath("%s/.perfconfig", home));
		struct stat st;

		if (user_config == NULL) {
			warning("Not enough memory to process %s/.perfconfig, "
				"ignoring it.", home);
			goto out;
		}

		if (stat(user_config, &st) < 0)
			goto out_free;

		if (st.st_uid && (st.st_uid != geteuid())) {
			warning("File %s not owned by current user or root, "
				"ignoring it.", user_config);
			goto out_free;
		}

		if (!st.st_size)
			goto out_free;

		ret += perf_config_from_file(fn, user_config, data);
		found += 1;
out_free:
		free(user_config);
	}
out:
	if (found == 0)
		return -1;
	return ret;
}