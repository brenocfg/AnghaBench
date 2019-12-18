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
struct tblentry {scalar_t__ cmdtype; int special; TYPE_1__ param; } ;
struct stat {int st_mode; scalar_t__ st_uid; scalar_t__ st_gid; } ;
struct cmdentry {scalar_t__ cmdtype; int special; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ CMDBUILTIN ; 
 scalar_t__ CMDFUNCTION ; 
 void* CMDNORMAL ; 
 scalar_t__ CMDUNKNOWN ; 
 int DO_ERR ; 
 int DO_NOFUNC ; 
 int EACCES ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 struct tblentry* cmdlookup (char const*,int) ; 
 int cmdtable_cd ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,char const*,char*) ; 
 int find_builtin (char const*,int*) ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  outfmt (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* padvance (char const**,char const**,char const*) ; 
 int /*<<< orphan*/  readcmdfile (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

void
find_command(const char *name, struct cmdentry *entry, int act,
    const char *path)
{
	struct tblentry *cmdp, loc_cmd;
	int idx;
	const char *opt;
	char *fullname;
	struct stat statb;
	int e;
	int i;
	int spec;
	int cd;

	/* If name contains a slash, don't use the hash table */
	if (strchr(name, '/') != NULL) {
		entry->cmdtype = CMDNORMAL;
		entry->u.index = 0;
		entry->special = 0;
		return;
	}

	cd = 0;

	/* If name is in the table, we're done */
	if ((cmdp = cmdlookup(name, 0)) != NULL) {
		if (cmdp->cmdtype == CMDFUNCTION && act & DO_NOFUNC)
			cmdp = NULL;
		else
			goto success;
	}

	/* Check for builtin next */
	if ((i = find_builtin(name, &spec)) >= 0) {
		INTOFF;
		cmdp = cmdlookup(name, 1);
		if (cmdp->cmdtype == CMDFUNCTION)
			cmdp = &loc_cmd;
		cmdp->cmdtype = CMDBUILTIN;
		cmdp->param.index = i;
		cmdp->special = spec;
		INTON;
		goto success;
	}

	/* We have to search path. */

	e = ENOENT;
	idx = -1;
	for (;(fullname = padvance(&path, &opt, name)) != NULL;
	    stunalloc(fullname)) {
		idx++;
		if (opt) {
			if (strncmp(opt, "func", 4) == 0) {
				/* handled below */
			} else {
				continue; /* ignore unimplemented options */
			}
		}
		if (fullname[0] != '/')
			cd = 1;
		if (stat(fullname, &statb) < 0) {
			if (errno != ENOENT && errno != ENOTDIR)
				e = errno;
			continue;
		}
		e = EACCES;	/* if we fail, this will be the error */
		if (!S_ISREG(statb.st_mode))
			continue;
		if (opt) {		/* this is a %func directory */
			readcmdfile(fullname);
			if ((cmdp = cmdlookup(name, 0)) == NULL || cmdp->cmdtype != CMDFUNCTION)
				error("%s not defined in %s", name, fullname);
			stunalloc(fullname);
			goto success;
		}
#ifdef notdef
		if (statb.st_uid == geteuid()) {
			if ((statb.st_mode & 0100) == 0)
				goto loop;
		} else if (statb.st_gid == getegid()) {
			if ((statb.st_mode & 010) == 0)
				goto loop;
		} else {
			if ((statb.st_mode & 01) == 0)
				goto loop;
		}
#endif
		TRACE(("searchexec \"%s\" returns \"%s\"\n", name, fullname));
		INTOFF;
		stunalloc(fullname);
		cmdp = cmdlookup(name, 1);
		if (cmdp->cmdtype == CMDFUNCTION)
			cmdp = &loc_cmd;
		cmdp->cmdtype = CMDNORMAL;
		cmdp->param.index = idx;
		cmdp->special = 0;
		INTON;
		goto success;
	}

	if (act & DO_ERR) {
		if (e == ENOENT || e == ENOTDIR)
			outfmt(out2, "%s: not found\n", name);
		else
			outfmt(out2, "%s: %s\n", name, strerror(e));
	}
	entry->cmdtype = CMDUNKNOWN;
	entry->u.index = 0;
	entry->special = 0;
	return;

success:
	if (cd)
		cmdtable_cd = 1;
	entry->cmdtype = cmdp->cmdtype;
	entry->u = cmdp->param;
	entry->special = cmdp->special;
}