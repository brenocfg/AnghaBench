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
struct TYPE_2__ {int index; int /*<<< orphan*/  func; } ;
struct tblentry {scalar_t__ cmdtype; TYPE_1__ param; int /*<<< orphan*/  cmdname; } ;

/* Variables and functions */
 scalar_t__ CMDBUILTIN ; 
 scalar_t__ CMDFUNCTION ; 
 scalar_t__ CMDNORMAL ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  ckfree (char*) ; 
 char* commandtext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  getfuncnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out1c (char) ; 
 int /*<<< orphan*/  out1fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out1str (char*) ; 
 char* padvance (char const**,char const**,int /*<<< orphan*/ ) ; 
 char* pathval () ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

__attribute__((used)) static void
printentry(struct tblentry *cmdp, int verbose)
{
	int idx;
	const char *path, *opt;
	char *name;

	if (cmdp->cmdtype == CMDNORMAL) {
		idx = cmdp->param.index;
		path = pathval();
		do {
			name = padvance(&path, &opt, cmdp->cmdname);
			stunalloc(name);
		} while (--idx >= 0);
		out1str(name);
	} else if (cmdp->cmdtype == CMDBUILTIN) {
		out1fmt("builtin %s", cmdp->cmdname);
	} else if (cmdp->cmdtype == CMDFUNCTION) {
		out1fmt("function %s", cmdp->cmdname);
		if (verbose) {
			INTOFF;
			name = commandtext(getfuncnode(cmdp->param.func));
			out1c(' ');
			out1str(name);
			ckfree(name);
			INTON;
		}
#ifdef DEBUG
	} else {
		error("internal error: cmdtype %d", cmdp->cmdtype);
#endif
	}
	out1c('\n');
}