#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dt_cpp_argc; int dt_cpp_args; char** dt_cpp_argv; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (char**,int) ; 
 char** realloc (char**,int) ; 
 char* strdup (char const*) ; 

char *
dt_cpp_add_arg(dtrace_hdl_t *dtp, const char *str)
{
	char *arg;

	if (dtp->dt_cpp_argc == dtp->dt_cpp_args) {
		int olds = dtp->dt_cpp_args;
		int news = olds * 2;
		char **argv = realloc(dtp->dt_cpp_argv, sizeof (char *) * news);

		if (argv == NULL)
			return (NULL);

		bzero(&argv[olds], sizeof (char *) * olds);
		dtp->dt_cpp_argv = argv;
		dtp->dt_cpp_args = news;
	}

	if ((arg = strdup(str)) == NULL)
		return (NULL);

	assert(dtp->dt_cpp_argc < dtp->dt_cpp_args);
	dtp->dt_cpp_argv[dtp->dt_cpp_argc++] = arg;
	return (arg);
}