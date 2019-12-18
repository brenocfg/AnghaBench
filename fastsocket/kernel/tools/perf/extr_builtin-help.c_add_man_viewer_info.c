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
 int add_man_viewer_cmd (char const*,int,char const*) ; 
 int add_man_viewer_path (char const*,int,char const*) ; 
 int config_error_nonbool (char const*) ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static int add_man_viewer_info(const char *var, const char *value)
{
	const char *name = var + 4;
	const char *subkey = strrchr(name, '.');

	if (!subkey)
		return error("Config with no key for man viewer: %s", name);

	if (!strcmp(subkey, ".path")) {
		if (!value)
			return config_error_nonbool(var);
		return add_man_viewer_path(name, subkey - name, value);
	}
	if (!strcmp(subkey, ".cmd")) {
		if (!value)
			return config_error_nonbool(var);
		return add_man_viewer_cmd(name, subkey - name, value);
	}

	warning("'%s': unsupported man viewer sub key.", subkey);
	return 0;
}