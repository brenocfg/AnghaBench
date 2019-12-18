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
struct option {unsigned long flag; int val; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,char*,char*) ; 
 unsigned long simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 char* strsep (char**,char*) ; 

int smb_getopt(char *caller, char **options, struct option *opts,
	       char **optopt, char **optarg, unsigned long *flag,
	       unsigned long *value)
{
	char *token;
	char *val;
	int i;

	do {
		if ((token = strsep(options, ",")) == NULL)
			return 0;
	} while (*token == '\0');
	*optopt = token;

	*optarg = NULL;
	if ((val = strchr (token, '=')) != NULL) {
		*val++ = 0;
		if (value)
			*value = simple_strtoul(val, NULL, 0);
		*optarg = val;
	}

	for (i = 0; opts[i].name != NULL; i++) {
		if (!strcmp(opts[i].name, token)) {
			if (!opts[i].flag && (!val || !*val)) {
				printk("%s: the %s option requires an argument\n",
				       caller, token);
				return -1;
			}

			if (flag && opts[i].flag)
				*flag |= opts[i].flag;

			return opts[i].val;
		}
	}
	printk("%s: Unrecognized mount option %s\n", caller, token);
	return -1;
}