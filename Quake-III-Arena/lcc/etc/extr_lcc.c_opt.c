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
 scalar_t__ Eflag ; 
 scalar_t__ Sflag ; 
 int /*<<< orphan*/  alist ; 
 int /*<<< orphan*/  append (char*,int /*<<< orphan*/ ) ; 
 char* basepath (int /*<<< orphan*/ ) ; 
 scalar_t__ cflag ; 
 int /*<<< orphan*/  clist ; 
 char** com ; 
 char* concat (char*,char*) ; 
 int /*<<< orphan*/ * cpp ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 char* first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  ilist ; 
 int /*<<< orphan*/ * include ; 
 int /*<<< orphan*/ * llist ; 
 int /*<<< orphan*/  option (char*) ; 
 int /*<<< orphan*/  plist ; 
 char* progname ; 
 char* rcsid ; 
 char* replace (char*,char,char) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/ * suffixes ; 
 char* tempdir ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void opt(char *arg) {
	switch (arg[1]) {	/* multi-character options */
	case 'W':	/* -Wxarg */
		if (arg[2] && arg[3])
			switch (arg[2]) {
			case 'o':
				if (option(&arg[3]))
					return;
				break;
			case 'p':
				plist = append(&arg[3], plist);
				return;
			case 'f':
				if (strcmp(&arg[3], "-C") || option("-b")) {
					clist = append(&arg[3], clist);
					return;
				}
				break; /* and fall thru */
			case 'a':
				alist = append(&arg[3], alist);
				return;
			case 'l':
				llist[0] = append(&arg[3], llist[0]);
				return;
			}
		fprintf(stderr, "%s: %s ignored\n", progname, arg);
		return;
	case 'd':	/* -dn */
		arg[1] = 's';
		clist = append(arg, clist);
		return;
	case 't':	/* -t -tname -tempdir=dir */
		if (strncmp(arg, "-tempdir=", 9) == 0)
			tempdir = arg + 9;
		else
			clist = append(arg, clist);
		return;
	case 'p':	/* -p -pg */
		if (option(arg))
			clist = append(arg, clist);
		else
			fprintf(stderr, "%s: %s ignored\n", progname, arg);
		return;
	case 'D':	/* -Dname -Dname=def */
	case 'U':	/* -Uname */
	case 'I':	/* -Idir */
		plist = append(arg, plist);
		return;
	case 'B':	/* -Bdir -Bstatic -Bdynamic */
#ifdef sparc
		if (strcmp(arg, "-Bstatic") == 0 || strcmp(arg, "-Bdynamic") == 0)
			llist[1] = append(arg, llist[1]);
		else
#endif	
		{
		static char *path;
		if (path)
			error("-B overwrites earlier option", 0);
		path = arg + 2;
		if (strstr(com[1], "win32") != NULL)
			com[0] = concat(replace(path, '/', '\\'), concat("rcc", first(suffixes[4])));
		else
			com[0] = concat(path, "rcc");
		if (path[0] == 0)
			error("missing directory in -B option", 0);
		}
		return;
	case 'h':
		if (strcmp(arg, "-help") == 0) {
			static int printed = 0;
	case '?':
			if (!printed)
				help();
			printed = 1;
			return;
		}
#ifdef linux
	case 's':
		if (strcmp(arg,"-static") == 0) {
			if (!option(arg))
				fprintf(stderr, "%s: %s ignored\n", progname, arg);
			return;
		}
#endif         
	}
	if (arg[2] == 0)
		switch (arg[1]) {	/* single-character options */
		case 'S':
			Sflag++;
			return;
		case 'O':
			fprintf(stderr, "%s: %s ignored\n", progname, arg);
			return;
		case 'A': case 'n': case 'w': case 'P':
			clist = append(arg, clist);
			return;
		case 'g': case 'b':
			if (option(arg))
				clist = append(arg[1] == 'g' ? "-g2" : arg, clist);
			else
				fprintf(stderr, "%s: %s ignored\n", progname, arg);
			return;
		case 'G':
			if (option(arg)) {
				clist = append("-g3", clist);
				llist[0] = append("-N", llist[0]);
			} else
				fprintf(stderr, "%s: %s ignored\n", progname, arg);
			return;
		case 'E':
			Eflag++;
			return;
		case 'c':
			cflag++;
			return;
		case 'N':
			if (strcmp(basepath(cpp[0]), "gcc-cpp") == 0)
				plist = append("-nostdinc", plist);
			include[0] = 0;
			ilist = 0;
			return;
		case 'v':
			if (verbose++ == 0) {
				if (strcmp(basepath(cpp[0]), "gcc-cpp") == 0)
					plist = append(arg, plist);
				clist = append(arg, clist);
				fprintf(stderr, "%s %s\n", progname, rcsid);
			}
			return;
		}
	if (cflag || Sflag || Eflag)
		fprintf(stderr, "%s: %s ignored\n", progname, arg);
	else
		llist[1] = append(arg, llist[1]);
}