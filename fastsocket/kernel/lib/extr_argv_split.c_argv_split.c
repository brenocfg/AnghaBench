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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  argv_free (char**) ; 
 int count_argc (char const*) ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 char** kzalloc (int,int /*<<< orphan*/ ) ; 
 char* skip_arg (char const*) ; 
 char* skip_spaces (char const*) ; 

char **argv_split(gfp_t gfp, const char *str, int *argcp)
{
	int argc = count_argc(str);
	char **argv = kzalloc(sizeof(*argv) * (argc+1), gfp);
	char **argvp;

	if (argv == NULL)
		goto out;

	if (argcp)
		*argcp = argc;

	argvp = argv;

	while (*str) {
		str = skip_spaces(str);

		if (*str) {
			const char *p = str;
			char *t;

			str = skip_arg(str);

			t = kstrndup(p, str-p, gfp);
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