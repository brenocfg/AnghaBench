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
 int /*<<< orphan*/  add_cmdname (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  autocorrect ; 
 int /*<<< orphan*/  perf_config_int (char const*,char const*) ; 
 int perf_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int perf_unknown_cmd_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "help.autocorrect"))
		autocorrect = perf_config_int(var,value);
	/* Also use aliases for command lookup */
	if (!prefixcmp(var, "alias."))
		add_cmdname(&aliases, var + 6, strlen(var + 6));

	return perf_default_config(var, value, cb);
}