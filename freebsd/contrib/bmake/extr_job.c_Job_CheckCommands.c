#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  commands; } ;
struct TYPE_9__ {int type; int flags; char* fname; int lineno; char* name; int /*<<< orphan*/  children; int /*<<< orphan*/  commands; } ;
typedef  TYPE_1__ GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 TYPE_4__* DEFAULT ; 
 scalar_t__ Dir_MTime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int FROM_DEPEND ; 
 int /*<<< orphan*/  IMPSRC ; 
 int /*<<< orphan*/  Job_RunTarget (char*,char*) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Make_HandleUse (TYPE_4__*,TYPE_1__*) ; 
 int OP_LIB ; 
 scalar_t__ OP_NOP (int) ; 
 int OP_OPTIONAL ; 
 int OP_SPECIAL ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Var_Value (int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ keepgoing ; 
 char* makeDependfile ; 
 char* progname ; 
 int /*<<< orphan*/  stdout ; 
 void stub1 (char const*,...) ; 

Boolean
Job_CheckCommands(GNode *gn, void (*abortProc)(const char *, ...))
{
    if (OP_NOP(gn->type) && Lst_IsEmpty(gn->commands) &&
	((gn->type & OP_LIB) == 0 || Lst_IsEmpty(gn->children))) {
	/*
	 * No commands. Look for .DEFAULT rule from which we might infer
	 * commands
	 */
	if ((DEFAULT != NULL) && !Lst_IsEmpty(DEFAULT->commands) &&
		(gn->type & OP_SPECIAL) == 0) {
	    char *p1;
	    /*
	     * Make only looks for a .DEFAULT if the node was never the
	     * target of an operator, so that's what we do too. If
	     * a .DEFAULT was given, we substitute its commands for gn's
	     * commands and set the IMPSRC variable to be the target's name
	     * The DEFAULT node acts like a transformation rule, in that
	     * gn also inherits any attributes or sources attached to
	     * .DEFAULT itself.
	     */
	    Make_HandleUse(DEFAULT, gn);
	    Var_Set(IMPSRC, Var_Value(TARGET, gn, &p1), gn, 0);
	    free(p1);
	} else if (Dir_MTime(gn, 0) == 0 && (gn->type & OP_SPECIAL) == 0) {
	    /*
	     * The node wasn't the target of an operator we have no .DEFAULT
	     * rule to go on and the target doesn't already exist. There's
	     * nothing more we can do for this branch. If the -k flag wasn't
	     * given, we stop in our tracks, otherwise we just don't update
	     * this node's parents so they never get examined.
	     */
	    static const char msg[] = ": don't know how to make";

	    if (gn->flags & FROM_DEPEND) {
		if (!Job_RunTarget(".STALE", gn->fname))
		    fprintf(stdout, "%s: %s, %d: ignoring stale %s for %s\n",
			progname, gn->fname, gn->lineno, makeDependfile,
			gn->name);
		return TRUE;
	    }

	    if (gn->type & OP_OPTIONAL) {
		(void)fprintf(stdout, "%s%s %s (ignored)\n", progname,
		    msg, gn->name);
		(void)fflush(stdout);
	    } else if (keepgoing) {
		(void)fprintf(stdout, "%s%s %s (continuing)\n", progname,
		    msg, gn->name);
		(void)fflush(stdout);
  		return FALSE;
	    } else {
		(*abortProc)("%s%s %s. Stop", progname, msg, gn->name);
		return FALSE;
	    }
	}
    }
    return TRUE;
}