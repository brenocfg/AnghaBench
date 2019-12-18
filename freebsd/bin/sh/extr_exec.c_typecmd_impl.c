#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int index; } ;
struct tblentry {int cmdtype; int /*<<< orphan*/  special; TYPE_1__ param; } ;
struct cmdentry {int cmdtype; int /*<<< orphan*/  special; TYPE_1__ u; } ;
struct alias {int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  CMDBUILTIN 130 
#define  CMDFUNCTION 129 
#define  CMDNORMAL 128 
 int TYPECMD_SMALLV ; 
 int TYPECMD_TYPE ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  clearcmdentry () ; 
 struct tblentry* cmdlookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eaccess (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ equal (char const* const,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  find_command (char*,struct cmdentry*,int /*<<< orphan*/ ,char const*) ; 
 struct alias* lookupalias (char*,int) ; 
 int /*<<< orphan*/  out1 ; 
 int /*<<< orphan*/  out1fmt (char*,char*,...) ; 
 int /*<<< orphan*/  out1qstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  outcslow (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outfmt (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* padvance (char const**,char const**,char*) ; 
 char** parsekwd ; 
 char const* pathval () ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

int
typecmd_impl(int argc, char **argv, int cmd, const char *path)
{
	struct cmdentry entry;
	struct tblentry *cmdp;
	const char *const *pp;
	struct alias *ap;
	int i;
	int error1 = 0;

	if (path != pathval())
		clearcmdentry();

	for (i = 1; i < argc; i++) {
		/* First look at the keywords */
		for (pp = parsekwd; *pp; pp++)
			if (**pp == *argv[i] && equal(*pp, argv[i]))
				break;

		if (*pp) {
			if (cmd == TYPECMD_SMALLV)
				out1fmt("%s\n", argv[i]);
			else
				out1fmt("%s is a shell keyword\n", argv[i]);
			continue;
		}

		/* Then look at the aliases */
		if ((ap = lookupalias(argv[i], 1)) != NULL) {
			if (cmd == TYPECMD_SMALLV) {
				out1fmt("alias %s=", argv[i]);
				out1qstr(ap->val);
				outcslow('\n', out1);
			} else
				out1fmt("%s is an alias for %s\n", argv[i],
				    ap->val);
			continue;
		}

		/* Then check if it is a tracked alias */
		if ((cmdp = cmdlookup(argv[i], 0)) != NULL) {
			entry.cmdtype = cmdp->cmdtype;
			entry.u = cmdp->param;
			entry.special = cmdp->special;
		}
		else {
			/* Finally use brute force */
			find_command(argv[i], &entry, 0, path);
		}

		switch (entry.cmdtype) {
		case CMDNORMAL: {
			if (strchr(argv[i], '/') == NULL) {
				const char *path2 = path;
				const char *opt2;
				char *name;
				int j = entry.u.index;
				do {
					name = padvance(&path2, &opt2, argv[i]);
					stunalloc(name);
				} while (--j >= 0);
				if (cmd == TYPECMD_SMALLV)
					out1fmt("%s\n", name);
				else
					out1fmt("%s is%s %s\n", argv[i],
					    (cmdp && cmd == TYPECMD_TYPE) ?
						" a tracked alias for" : "",
					    name);
			} else {
				if (eaccess(argv[i], X_OK) == 0) {
					if (cmd == TYPECMD_SMALLV)
						out1fmt("%s\n", argv[i]);
					else
						out1fmt("%s is %s\n", argv[i],
						    argv[i]);
				} else {
					if (cmd != TYPECMD_SMALLV)
						outfmt(out2, "%s: %s\n",
						    argv[i], strerror(errno));
					error1 |= 127;
				}
			}
			break;
		}
		case CMDFUNCTION:
			if (cmd == TYPECMD_SMALLV)
				out1fmt("%s\n", argv[i]);
			else
				out1fmt("%s is a shell function\n", argv[i]);
			break;

		case CMDBUILTIN:
			if (cmd == TYPECMD_SMALLV)
				out1fmt("%s\n", argv[i]);
			else if (entry.special)
				out1fmt("%s is a special shell builtin\n",
				    argv[i]);
			else
				out1fmt("%s is a shell builtin\n", argv[i]);
			break;

		default:
			if (cmd != TYPECMD_SMALLV)
				outfmt(out2, "%s: not found\n", argv[i]);
			error1 |= 127;
			break;
		}
	}

	if (path != pathval())
		clearcmdentry();

	return error1;
}