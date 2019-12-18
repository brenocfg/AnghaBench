#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* progend ) () ;int /*<<< orphan*/  (* stabend ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* stabinit ) (int /*<<< orphan*/ ,int,char**) ;int /*<<< orphan*/  (* progbeg ) (int,char**) ;} ;
struct TYPE_10__ {char* name; TYPE_7__* ir; } ;
struct TYPE_9__ {scalar_t__ end; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; scalar_t__ x; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/ * Symbol ;
typedef  TYPE_1__ Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  GLOBAL ; 
 TYPE_7__* IR ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  apply (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* bindings ; 
 int /*<<< orphan*/  deallocate (int /*<<< orphan*/ ) ; 
 scalar_t__ errcnt ; 
 TYPE_4__ events ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize () ; 
 int /*<<< orphan*/  firstfile ; 
 int /*<<< orphan*/  foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gettok () ; 
 int glevel ; 
 int /*<<< orphan*/  identifiers ; 
 int /*<<< orphan*/  init (int,char**) ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  loci ; 
 int /*<<< orphan*/ * ltov (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  program () ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  symbols ; 
 int /*<<< orphan*/  t ; 
 int /*<<< orphan*/  types ; 
 int /*<<< orphan*/  typestab ; 
 scalar_t__ xref ; 

int main(int argc, char *argv[]) {
	int i, j;
	for (i = argc - 1; i > 0; i--)
		if (strncmp(argv[i], "-target=", 8) == 0)
			break;
	if (i > 0) {
		char *s = strchr(argv[i], '\\');
		if (s != NULL)
			*s = '/';
		for (j = 0; bindings[j].name && bindings[j].ir; j++)
			if (strcmp(&argv[i][8], bindings[j].name) == 0) {
				IR = bindings[j].ir;
				break;
			}
		if (s != NULL)
			*s = '\\';
	}
	if (!IR) {
		fprint(stderr, "%s: unknown target", argv[0]);
		if (i > 0)
			fprint(stderr, " `%s'", &argv[i][8]);
		fprint(stderr, "; must specify one of\n");
		for (i = 0; bindings[i].name; i++)
			fprint(stderr, "\t-target=%s\n", bindings[i].name);
		exit(EXIT_FAILURE);
	}
	init(argc, argv);
	t = gettok();
	(*IR->progbeg)(argc, argv);
	if (glevel && IR->stabinit)
		(*IR->stabinit)(firstfile, argc, argv);
	program();
	if (events.end)
		apply(events.end, NULL, NULL);
	memset(&events, 0, sizeof events);
	if (glevel || xref) {
		Symbol symroot = NULL;
		Coordinate src;
		foreach(types,       GLOBAL, typestab, &symroot);
		foreach(identifiers, GLOBAL, typestab, &symroot);
		src.file = firstfile;
		src.x = 0;
		src.y = lineno;
		if ((glevel > 2 || xref) && IR->stabend)
			(*IR->stabend)(&src, symroot,
				ltov(&loci,    PERM),
				ltov(&symbols, PERM), NULL);
		else if (IR->stabend)
			(*IR->stabend)(&src, NULL, NULL, NULL, NULL);
	}
	finalize();
	(*IR->progend)();
	deallocate(PERM);
	return errcnt > 0;
}