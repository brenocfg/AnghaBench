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
 int /*<<< orphan*/  emu_set_defconfig () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  keys_parse_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  parse (char*,char*,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int seek_sect (int /*<<< orphan*/ *,char const*) ; 

int config_readsect(const char *fname, const char *section)
{
	char line[128], *var, *val;
	int keys_encountered = 0;
	FILE *f;
	int ret;

	f = fopen(fname, "r");
	if (f == NULL) return -1;

	if (section != NULL)
	{
		/* for game_def.cfg only */
		ret = seek_sect(f, section);
		if (!ret) {
			lprintf("config_readsect: %s: missing section [%s]\n", fname, section);
			fclose(f);
			return -1;
		}
	}

	emu_set_defconfig();

	while (!feof(f))
	{
		ret = config_get_var_val(f, line, sizeof(line), &var, &val);
		if (ret ==  0) break;
		if (ret == -1) continue;

		parse(var, val, &keys_encountered);
	}

	if (keys_encountered) {
		rewind(f);
		keys_parse_all(f);
	}

	fclose(f);

	lprintf("config_readsect: loaded from %s", fname);
	if (section != NULL)
		lprintf(" [%s]", section);
	printf("\n");

	return 0;
}