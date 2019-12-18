#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct block {struct block* link; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  reached; int /*<<< orphan*/ * rules; struct TYPE_7__* link; } ;
typedef  TYPE_1__* Nonterm ;

/* Variables and functions */
 int EOF ; 
 int Tflag ; 
 int /*<<< orphan*/  ckreach (scalar_t__) ; 
 int /*<<< orphan*/  emitclosure (TYPE_1__*) ; 
 int /*<<< orphan*/  emitdefs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitheader () ; 
 int /*<<< orphan*/  emitkids (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitlabel (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitnts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitrule (TYPE_1__*) ; 
 int /*<<< orphan*/  emitstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitstruct (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errcnt ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  free (struct block*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * infp ; 
 struct block* memlist ; 
 int /*<<< orphan*/  nrules ; 
 int /*<<< orphan*/  ntnumber ; 
 TYPE_1__* nts ; 
 int /*<<< orphan*/ * outfp ; 
 char* prefix ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rules ; 
 scalar_t__ start ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  terms ; 
 int /*<<< orphan*/  yyerror (char*,char*,...) ; 
 int /*<<< orphan*/  yyparse () ; 

int main(int argc, char *argv[]) {
	int c, i;
	Nonterm p;
	
	for (i = 1; i < argc; i++)
		if (strcmp(argv[i], "-T") == 0)
			Tflag = 1;
		else if (strncmp(argv[i], "-p", 2) == 0 && argv[i][2])
			prefix = &argv[i][2];
		else if (strncmp(argv[i], "-p", 2) == 0 && i + 1 < argc)
			prefix = argv[++i];
		else if (*argv[i] == '-' && argv[i][1]) {
			yyerror("usage: %s [-T | -p prefix]... [ [ input ] output ] \n",
				argv[0]);
			exit(1);
		} else if (infp == NULL) {
			if (strcmp(argv[i], "-") == 0)
				infp = stdin;
			else if ((infp = fopen(argv[i], "r")) == NULL) {
				yyerror("%s: can't read `%s'\n", argv[0], argv[i]);
				exit(1);
			}
		} else if (outfp == NULL) {
			if (strcmp(argv[i], "-") == 0)
				outfp = stdout;
			if ((outfp = fopen(argv[i], "w")) == NULL) {
				yyerror("%s: can't write `%s'\n", argv[0], argv[i]);
				exit(1);
			}
		}
	if (infp == NULL)
		infp = stdin;
	if (outfp == NULL)
		outfp = stdout;
	yyparse();
	if (start)
		ckreach(start);
	for (p = nts; p; p = p->link) {
		if (p->rules == NULL)
			yyerror("undefined nonterminal `%s'\n", p->name);
		if (!p->reached)
			yyerror("can't reach nonterminal `%s'\n", p->name);
	}
	emitheader();
	emitdefs(nts, ntnumber);
	emitstruct(nts, ntnumber);
	emitnts(rules, nrules);
	emitstring(rules);
	emitrule(nts);
	emitclosure(nts);
	if (start)
		emitlabel(terms, start, ntnumber);
	emitkids(rules, nrules);
	if (!feof(infp))
		while ((c = getc(infp)) != EOF)
			putc(c, outfp);
	while (memlist) {	/* for purify */
		struct block *q = memlist->link;
		free(memlist);
		memlist = q;
	}
	return errcnt > 0;
}