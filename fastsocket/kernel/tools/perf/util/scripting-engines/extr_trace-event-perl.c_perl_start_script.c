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
 int /*<<< orphan*/  ERRSV ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const**) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  my_perl ; 
 int /*<<< orphan*/  perl_alloc () ; 
 int /*<<< orphan*/  perl_construct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perl_free (int /*<<< orphan*/ ) ; 
 scalar_t__ perl_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,char**) ; 
 scalar_t__ perl_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_start_sub () ; 
 int /*<<< orphan*/  xs_init ; 

__attribute__((used)) static int perl_start_script(const char *script, int argc, const char **argv)
{
	const char **command_line;
	int i, err = 0;

	command_line = malloc((argc + 2) * sizeof(const char *));
	command_line[0] = "";
	command_line[1] = script;
	for (i = 2; i < argc + 2; i++)
		command_line[i] = argv[i - 2];

	my_perl = perl_alloc();
	perl_construct(my_perl);

	if (perl_parse(my_perl, xs_init, argc + 2, (char **)command_line,
		       (char **)NULL)) {
		err = -1;
		goto error;
	}

	if (perl_run(my_perl)) {
		err = -1;
		goto error;
	}

	if (SvTRUE(ERRSV)) {
		err = -1;
		goto error;
	}

	run_start_sub();

	free(command_line);
	return 0;
error:
	perl_free(my_perl);
	free(command_line);

	return err;
}