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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lprintf (char*,char*,...) ; 
 int /*<<< orphan*/  mystrip (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

int config_get_var_val(void *file, char *line, int lsize, char **rvar, char **rval)
{
	char *var, *val, *tmp;
	FILE *f = file;
	int len, i;

	tmp = fgets(line, lsize, f);
	if (tmp == NULL) return 0;

	if (line[0] == '[') return 0; // other section

	// strip comments, linefeed, spaces..
	len = strlen(line);
	for (i = 0; i < len; i++)
		if (line[i] == '#' || line[i] == '\r' || line[i] == '\n') { line[i] = 0; break; }
	mystrip(line);
	len = strlen(line);
	if (len <= 0) return -1;;

	// get var and val
	for (i = 0; i < len; i++)
		if (line[i] == '=') break;
	if (i >= len || strchr(&line[i+1], '=') != NULL) {
		lprintf("config_readsect: can't parse: %s\n", line);
		return -1;
	}
	line[i] = 0;
	var = line;
	val = &line[i+1];
	mystrip(var);
	mystrip(val);

#ifndef _MSC_VER
	if (strlen(var) == 0 || (strlen(val) == 0 && strncasecmp(var, "bind", 4) != 0)) {
		lprintf("config_readsect: something's empty: \"%s\" = \"%s\"\n", var, val);
		return -1;;
	}
#endif

	*rvar = var;
	*rval = val;
	return 1;
}