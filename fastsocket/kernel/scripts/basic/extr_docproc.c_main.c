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
 int /*<<< orphan*/  SEEK_SET ; 
 void* adddep ; 
 void* adddep2 ; 
 void* defaultline ; 
 void* docsect ; 
 void* docsection ; 
 int /*<<< orphan*/  exit (int) ; 
 int exitstatus ; 
 void* externalfunctions ; 
 void* extfunc ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 void* find_export_symbols ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* getenv (char*) ; 
 void* internalfunctions ; 
 void* intfunc ; 
 int /*<<< orphan*/ * kernsrctree ; 
 void* noaction ; 
 void* noaction2 ; 
 int /*<<< orphan*/  parse_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* printline ; 
 void* singfunc ; 
 void* singlefunctions ; 
 int /*<<< orphan*/ * srctree ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* symbolsonly ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	FILE * infile;

	srctree = getenv("SRCTREE");
	if (!srctree)
		srctree = getcwd(NULL, 0);
	kernsrctree = getenv("KBUILD_SRC");
	if (!kernsrctree || !*kernsrctree)
		kernsrctree = srctree;
	if (argc != 3) {
		usage();
		exit(1);
	}
	/* Open file, exit on error */
	infile = fopen(argv[2], "r");
        if (infile == NULL) {
                fprintf(stderr, "docproc: ");
                perror(argv[2]);
                exit(2);
        }

	if (strcmp("doc", argv[1]) == 0)
	{
		/* Need to do this in two passes.
		 * First pass is used to collect all symbols exported
		 * in the various files;
		 * Second pass generate the documentation.
		 * This is required because some functions are declared
		 * and exported in different files :-((
		 */
		/* Collect symbols */
		defaultline       = noaction;
		internalfunctions = find_export_symbols;
		externalfunctions = find_export_symbols;
		symbolsonly       = find_export_symbols;
		singlefunctions   = noaction2;
		docsection        = noaction2;
		parse_file(infile);

		/* Rewind to start from beginning of file again */
		fseek(infile, 0, SEEK_SET);
		defaultline       = printline;
		internalfunctions = intfunc;
		externalfunctions = extfunc;
		symbolsonly       = printline;
		singlefunctions   = singfunc;
		docsection        = docsect;

		parse_file(infile);
	}
	else if (strcmp("depend", argv[1]) == 0)
	{
		/* Create first part of dependency chain
		 * file.tmpl */
		printf("%s\t", argv[2]);
		defaultline       = noaction;
		internalfunctions = adddep;
		externalfunctions = adddep;
		symbolsonly       = adddep;
		singlefunctions   = adddep2;
		docsection        = adddep2;
		parse_file(infile);
		printf("\n");
	}
	else
	{
		fprintf(stderr, "Unknown option: %s\n", argv[1]);
		exit(1);
	}
	fclose(infile);
	fflush(stdout);
	return exitstatus;
}