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
 int /*<<< orphan*/  G_STRLOC ; 
 int _putenv_s (char const*,char const*) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,char const*,char const*,...) ; 
 scalar_t__ g_setenv (char const*,char const*,int) ; 
 int /*<<< orphan*/  getenv (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int chassis_frontend_lua_setenv(const char *key, const char *value) {
	int r;
#if _WIN32
	r = _putenv_s(key, value);
#else
	r = g_setenv(key, value, 1) ? 0 : -1; /* g_setenv() returns TRUE/FALSE */
#endif

	if (0 == r) {
		/* the setenv() succeeded, double-check it */
		if (!getenv(key)) {
			/* check that getenv() returns what we did set */
			g_critical("%s: setting %s = %s failed: (getenv() == NULL)", G_STRLOC,
					key, value);
		} else if (0 != strcmp(getenv(key), value)) {
			g_critical("%s: setting %s = %s failed: (getenv() == %s)", G_STRLOC,
					key, value,
					getenv(key));
		}
	}

	return r;
}