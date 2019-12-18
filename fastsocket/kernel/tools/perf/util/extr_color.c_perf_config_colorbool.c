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
 char* getenv (char*) ; 
 int isatty (int) ; 
 scalar_t__ pager_in_use () ; 
 scalar_t__ pager_use_color ; 
 int /*<<< orphan*/  perf_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int perf_config_colorbool(const char *var, const char *value, int stdout_is_tty)
{
	if (value) {
		if (!strcasecmp(value, "never"))
			return 0;
		if (!strcasecmp(value, "always"))
			return 1;
		if (!strcasecmp(value, "auto"))
			goto auto_color;
	}

	/* Missing or explicit false to turn off colorization */
	if (!perf_config_bool(var, value))
		return 0;

	/* any normal truth value defaults to 'auto' */
 auto_color:
	if (stdout_is_tty < 0)
		stdout_is_tty = isatty(1);
	if (stdout_is_tty || (pager_in_use() && pager_use_color)) {
		char *term = getenv("TERM");
		if (term && strcmp(term, "dumb"))
			return 1;
	}
	return 0;
}