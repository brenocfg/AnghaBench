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
 int /*<<< orphan*/  argv_free (char**) ; 
 int count_argc (char const*) ; 
 char* skip_arg (char const*) ; 
 char* skip_sep (char const*) ; 
 char* strndup (char const*,int) ; 
 char** zalloc (int) ; 

char **argv_split(const char *str, int *argcp)
{
	int argc = count_argc(str);
	char **argv = zalloc(sizeof(*argv) * (argc+1));
	char **argvp;

	if (argv == NULL)
		goto out;

	if (argcp)
		*argcp = argc;

	argvp = argv;

	while (*str) {
		str = skip_sep(str);

		if (*str) {
			const char *p = str;
			char *t;

			str = skip_arg(str);

			t = strndup(p, str-p);
			if (t == NULL)
				goto fail;
			*argvp++ = t;
		}
	}
	*argvp = NULL;

out:
	return argv;

fail:
	argv_free(argv);
	return NULL;
}