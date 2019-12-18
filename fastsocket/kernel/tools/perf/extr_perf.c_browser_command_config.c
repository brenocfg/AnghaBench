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
struct pager_config {int val; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int perf_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int browser_command_config(const char *var, const char *value, void *data)
{
	struct pager_config *c = data;
	if (!prefixcmp(var, "tui.") && !strcmp(var + 4, c->cmd))
		c->val = perf_config_bool(var, value);
	if (!prefixcmp(var, "gtk.") && !strcmp(var + 4, c->cmd))
		c->val = perf_config_bool(var, value) ? 2 : 0;
	return 0;
}