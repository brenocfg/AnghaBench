#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; char* path; char* name; TYPE_1__* suffix; } ;
struct TYPE_8__ {int /*<<< orphan*/  searchPath; int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Arch_FindLib (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBSUFF ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OP_ARCHV ; 
 int OP_DEPS_FOUND ; 
 int OP_LIB ; 
 int /*<<< orphan*/  PREFIX ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffFindArchiveDeps (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SuffFindNormalDeps (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SuffSuffHasNameP ; 
 int /*<<< orphan*/  TARGET ; 
 int /*<<< orphan*/  Var_Set (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sufflist ; 

__attribute__((used)) static void
SuffFindDeps(GNode *gn, Lst slst)
{
    if (gn->type & OP_DEPS_FOUND) {
	/*
	 * If dependencies already found, no need to do it again...
	 */
	return;
    } else {
	gn->type |= OP_DEPS_FOUND;
    }
    /*
     * Make sure we have these set, may get revised below.
     */
    Var_Set(TARGET, gn->path ? gn->path : gn->name, gn, 0);
    Var_Set(PREFIX, gn->name, gn, 0);

    if (DEBUG(SUFF)) {
	fprintf(debug_file, "SuffFindDeps (%s)\n", gn->name);
    }

    if (gn->type & OP_ARCHV) {
	SuffFindArchiveDeps(gn, slst);
    } else if (gn->type & OP_LIB) {
	/*
	 * If the node is a library, it is the arch module's job to find it
	 * and set the TARGET variable accordingly. We merely provide the
	 * search path, assuming all libraries end in ".a" (if the suffix
	 * hasn't been defined, there's nothing we can do for it, so we just
	 * set the TARGET variable to the node's name in order to give it a
	 * value).
	 */
	LstNode	ln;
	Suff	*s;

	ln = Lst_Find(sufflist, LIBSUFF, SuffSuffHasNameP);
	if (gn->suffix)
	    gn->suffix->refCount--;
	if (ln != NULL) {
	    gn->suffix = s = (Suff *)Lst_Datum(ln);
	    gn->suffix->refCount++;
	    Arch_FindLib(gn, s->searchPath);
	} else {
	    gn->suffix = NULL;
	    Var_Set(TARGET, gn->name, gn, 0);
	}
	/*
	 * Because a library (-lfoo) target doesn't follow the standard
	 * filesystem conventions, we don't set the regular variables for
	 * the thing. .PREFIX is simply made empty...
	 */
	Var_Set(PREFIX, "", gn, 0);
    } else {
	SuffFindNormalDeps(gn, slst);
    }
}