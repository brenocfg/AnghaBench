#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_5__ {int type; char* name; void* mtime; int /*<<< orphan*/  children; int /*<<< orphan*/  commands; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 scalar_t__ Dir_MTime (TYPE_1__*,int) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE ; 
 scalar_t__ NoExecute (TYPE_1__*) ; 
 int OP_SAVE_CMDS ; 
 int OP_WAIT ; 
 char* Targ_FmtTime (void*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 void* now ; 

time_t
Make_Recheck(GNode *gn)
{
    time_t mtime = Dir_MTime(gn, 1);

#ifndef RECHECK
    /*
     * We can't re-stat the thing, but we can at least take care of rules
     * where a target depends on a source that actually creates the
     * target, but only if it has changed, e.g.
     *
     * parse.h : parse.o
     *
     * parse.o : parse.y
     *  	yacc -d parse.y
     *  	cc -c y.tab.c
     *  	mv y.tab.o parse.o
     *  	cmp -s y.tab.h parse.h || mv y.tab.h parse.h
     *
     * In this case, if the definitions produced by yacc haven't changed
     * from before, parse.h won't have been updated and gn->mtime will
     * reflect the current modification time for parse.h. This is
     * something of a kludge, I admit, but it's a useful one..
     * XXX: People like to use a rule like
     *
     * FRC:
     *
     * To force things that depend on FRC to be made, so we have to
     * check for gn->children being empty as well...
     */
    if (!Lst_IsEmpty(gn->commands) || Lst_IsEmpty(gn->children)) {
	gn->mtime = now;
    }
#else
    /*
     * This is what Make does and it's actually a good thing, as it
     * allows rules like
     *
     *	cmp -s y.tab.h parse.h || cp y.tab.h parse.h
     *
     * to function as intended. Unfortunately, thanks to the stateless
     * nature of NFS (by which I mean the loose coupling of two clients
     * using the same file from a common server), there are times
     * when the modification time of a file created on a remote
     * machine will not be modified before the local stat() implied by
     * the Dir_MTime occurs, thus leading us to believe that the file
     * is unchanged, wreaking havoc with files that depend on this one.
     *
     * I have decided it is better to make too much than to make too
     * little, so this stuff is commented out unless you're sure it's ok.
     * -- ardeb 1/12/88
     */
    /*
     * Christos, 4/9/92: If we are  saving commands pretend that
     * the target is made now. Otherwise archives with ... rules
     * don't work!
     */
    if (NoExecute(gn) || (gn->type & OP_SAVE_CMDS) ||
	    (mtime == 0 && !(gn->type & OP_WAIT))) {
	if (DEBUG(MAKE)) {
	    fprintf(debug_file, " recheck(%s): update time from %s to now\n",
		   gn->name, Targ_FmtTime(gn->mtime));
	}
	gn->mtime = now;
    }
    else {
	if (DEBUG(MAKE)) {
	    fprintf(debug_file, " recheck(%s): current update time: %s\n",
		   gn->name, Targ_FmtTime(gn->mtime));
	}
    }
#endif
    return mtime;
}