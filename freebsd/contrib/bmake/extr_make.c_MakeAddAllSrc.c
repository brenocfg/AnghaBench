#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; char* path; char* name; scalar_t__ made; scalar_t__ mtime; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  ALLSRC ; 
 scalar_t__ MADE ; 
 int /*<<< orphan*/  MEMBER ; 
 int /*<<< orphan*/  OODATE ; 
 int OP_ARCHV ; 
 int OP_EXEC ; 
 int OP_INVISIBLE ; 
 int OP_JOIN ; 
 int OP_MARK ; 
 int OP_USE ; 
 int OP_USEBEFORE ; 
 int /*<<< orphan*/  Var_Append (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 char* Var_Value (int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ now ; 

__attribute__((used)) static int
MakeAddAllSrc(void *cgnp, void *pgnp)
{
    GNode	*cgn = (GNode *)cgnp;
    GNode	*pgn = (GNode *)pgnp;

    if (cgn->type & OP_MARK)
	return (0);
    cgn->type |= OP_MARK;

    if ((cgn->type & (OP_EXEC|OP_USE|OP_USEBEFORE|OP_INVISIBLE)) == 0) {
	char *child, *allsrc;
	char *p1 = NULL, *p2 = NULL;

	if (cgn->type & OP_ARCHV)
	    child = Var_Value(MEMBER, cgn, &p1);
	else
	    child = cgn->path ? cgn->path : cgn->name;
	if (cgn->type & OP_JOIN) {
	    allsrc = Var_Value(ALLSRC, cgn, &p2);
	} else {
	    allsrc = child;
	}
	if (allsrc != NULL)
		Var_Append(ALLSRC, allsrc, pgn);
	free(p2);
	if (pgn->type & OP_JOIN) {
	    if (cgn->made == MADE) {
		Var_Append(OODATE, child, pgn);
	    }
	} else if ((pgn->mtime < cgn->mtime) ||
		   (cgn->mtime >= now && cgn->made == MADE))
	{
	    /*
	     * It goes in the OODATE variable if the parent is younger than the
	     * child or if the child has been modified more recently than
	     * the start of the make. This is to keep pmake from getting
	     * confused if something else updates the parent after the
	     * make starts (shouldn't happen, I know, but sometimes it
	     * does). In such a case, if we've updated the kid, the parent
	     * is likely to have a modification time later than that of
	     * the kid and anything that relies on the OODATE variable will
	     * be hosed.
	     *
	     * XXX: This will cause all made children to go in the OODATE
	     * variable, even if they're not touched, if RECHECK isn't defined,
	     * since cgn->mtime is set to now in Make_Update. According to
	     * some people, this is good...
	     */
	    Var_Append(OODATE, child, pgn);
	}
	free(p1);
    }
    return (0);
}