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
 char* build_directory ; 
 int /*<<< orphan*/  conf_list ; 
 char* config_directory ; 
 int /*<<< orphan*/ * confp ; 
 int /*<<< orphan*/ * dtab ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  headers () ; 
 int /*<<< orphan*/  makefile () ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  mkioconf () ; 
 char* object_directory ; 
 scalar_t__ opt ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  profiling ; 
 char* source_directory ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ yyparse () ; 

int
main(int argc, char *argv[])
{

	source_directory = "..";	/* default */
	object_directory = "..";
	config_directory = (char *) 0;
	while ((argc > 1) && (argv[1][0] == '-')) {
		char		*c;

		argv++; argc--;
		for (c = &argv[0][1]; *c ; c++) {
			switch (*c) {
				case 'b':
					build_directory = argv[1];
					goto check_arg;

				case 'd':
					source_directory = argv[1];
					goto check_arg;

				case 'o':
					object_directory = argv[1];
					goto check_arg;

				case 'c':
					config_directory = argv[1];

				 check_arg:
				 	if (argv[1] == (char *) 0)
						goto usage_error;
					argv++; argc--;
					break;

				case 'p':
					profiling++;
					break;
				default:
					goto usage_error;
			}
		}
	}
	if (config_directory == (char *) 0) {
		config_directory =
			malloc((unsigned) strlen(source_directory) + 6);
		(void) sprintf(config_directory, "%s/conf", source_directory);
	}
	if (argc != 2) {
		usage_error: ;
		fprintf(stderr, "usage: config [ -bcdo dir ] [ -p ] sysname\n");
		exit(1);
	}
	if (!build_directory)
		build_directory = argv[1];
	if (freopen(argv[1], "r", stdin) == NULL) {
		perror(argv[1]);
		exit(2);
	}
	dtab = NULL;
	confp = &conf_list;
	opt = 0;
	if (yyparse())
		exit(3);

	mkioconf();			/* ioconf.c */
	makefile();			/* build Makefile */
	headers();			/* make a lot of .h files */

	return 0;
}