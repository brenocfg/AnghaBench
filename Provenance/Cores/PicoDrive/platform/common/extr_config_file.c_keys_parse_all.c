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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int config_get_var_val (int /*<<< orphan*/ *,char*,int,char**,char**) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_config_bind_key (int,char*,int,int) ; 
 int in_config_parse_dev (char*) ; 
 int /*<<< orphan*/  in_unbind_all (int,int,int) ; 
 int /*<<< orphan*/  lprintf (char*,char*) ; 
 int /*<<< orphan*/  mystrip (char*) ; 
 int parse_bind_val (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static void keys_parse_all(FILE *f)
{
	char line[256], *var, *val;
	int dev_id = -1;
	int acts, type;
	int ret;

	while (!feof(f))
	{
		ret = config_get_var_val(f, line, sizeof(line), &var, &val);
		if (ret ==  0) break;
		if (ret == -1) continue;

		if (strcasecmp(var, "binddev") == 0) {
			dev_id = in_config_parse_dev(val);
			if (dev_id < 0) {
				printf("input: can't handle dev: %s\n", val);
				continue;
			}
			in_unbind_all(dev_id, -1, -1);
			continue;
		}
		if (dev_id < 0 || strncasecmp(var, "bind ", 5) != 0)
			continue;

		acts = parse_bind_val(val, &type);
		if (acts == -1) {
			lprintf("config: unhandled action \"%s\"\n", val);
			return;
		}

		mystrip(var + 5);
		in_config_bind_key(dev_id, var + 5, acts, type);
	}
}