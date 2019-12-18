#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  mods ;
struct TYPE_8__ {scalar_t__ oidlen; } ;
typedef  TYPE_1__ SmiNode ;
typedef  int /*<<< orphan*/  SmiModule ;

/* Variables and functions */
 int SMI_FLAG_ERRORS ; 
 int /*<<< orphan*/  SMI_NODEKIND_ANY ; 
 scalar_t__ close_node (scalar_t__,scalar_t__) ; 
 scalar_t__ cut ; 
 scalar_t__ do_typedef ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * last_node ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 scalar_t__ open_node (TYPE_1__*,scalar_t__,TYPE_1__**) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_it (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  print_typdefs (TYPE_1__*) ; 
 TYPE_1__* smiGetFirstNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int smiGetFlags () ; 
 int /*<<< orphan*/ * smiGetModule (char*) ; 
 TYPE_1__* smiGetNextNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smiInit (int /*<<< orphan*/ *) ; 
 char* smiLoadModule (char*) ; 
 int /*<<< orphan*/  smiSetFlags (int) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  tdefs_cleanup () ; 
 char* usgtxt ; 

int
main(int argc, char *argv[])
{
	int opt;
	int flags;
	SmiModule **mods;
	char *name;
	SmiNode *n, *last;
	u_int level;
	long u;
	char *end;

	smiInit(NULL);

	while ((opt = getopt(argc, argv, "c:Eeh")) != -1)
		switch (opt) {

		  case 'c':
			errno = 0;
			u = strtol(optarg, &end, 10);
			if (errno != 0)
				err(1, "argument to -c");
			if (*end != '\0')
				err(1, "%s: not a number", optarg);
			if (u < 0 || u > 5)
				err(1, "%s: out of range", optarg);
			cut = (u_int)u;
			break;

		  case 'E':
			do_typedef = 'E';
			break;

		  case 'e':
			do_typedef = 'e';
			break;

		  case 'h':
			fprintf(stderr, usgtxt);
			exit(0);
		}

	argc -= optind;
	argv += optind;

	flags = smiGetFlags();
	flags |= SMI_FLAG_ERRORS;
	smiSetFlags(flags);

	mods = malloc(sizeof(mods[0]) * argc);
	if (mods == NULL)
		err(1, NULL);

	for (opt = 0; opt < argc; opt++) {
		if ((name = smiLoadModule(argv[opt])) == NULL)
			err(1, "%s: cannot load", argv[opt]);
		mods[opt] = smiGetModule(name);
	}
	level = 0;
	last = NULL;
	for (opt = 0; opt < argc; opt++) {
		if (mods[opt] == NULL) /* smiGetModule failed above */
			continue;
		n = smiGetFirstNode(mods[opt], SMI_NODEKIND_ANY);
		if (n == NULL)
			continue;
		for (;;) {
			if (do_typedef == 0) {
				level = open_node(n, level, &last);
				print_it(n, level);
				last = n;
			} else
				print_typdefs(n);

			if (last_node == NULL ||
			    (n = smiGetNextNode(last_node, SMI_NODEKIND_ANY))
			    == NULL)
				break;
		}
	}
	if (last != NULL && do_typedef == 0)
		level = close_node(last->oidlen - 1, level - 1);
	else if (do_typedef != 0)
		tdefs_cleanup();

	return (0);
}