#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int unmade; char* name; int /*<<< orphan*/  iParents; int /*<<< orphan*/  children; int /*<<< orphan*/  parents; } ;
struct TYPE_11__ {char* name; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_2__ GNode ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Succ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Make_HandleUse (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffExpandChildren (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SuffGNHasNameP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* str_concat (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transforms ; 

__attribute__((used)) static Boolean
SuffApplyTransform(GNode *tGn, GNode *sGn, Suff *t, Suff *s)
{
    LstNode 	ln, nln;    /* General node */
    char    	*tname;	    /* Name of transformation rule */
    GNode   	*gn;	    /* Node for same */

    /*
     * Form the proper links between the target and source.
     */
    (void)Lst_AtEnd(tGn->children, sGn);
    (void)Lst_AtEnd(sGn->parents, tGn);
    tGn->unmade += 1;

    /*
     * Locate the transformation rule itself
     */
    tname = str_concat(s->name, t->name, 0);
    ln = Lst_Find(transforms, tname, SuffGNHasNameP);
    free(tname);

    if (ln == NULL) {
	/*
	 * Not really such a transformation rule (can happen when we're
	 * called to link an OP_MEMBER and OP_ARCHV node), so return
	 * FALSE.
	 */
	return(FALSE);
    }

    gn = (GNode *)Lst_Datum(ln);

    if (DEBUG(SUFF)) {
	fprintf(debug_file, "\tapplying %s -> %s to \"%s\"\n", s->name, t->name, tGn->name);
    }

    /*
     * Record last child for expansion purposes
     */
    ln = Lst_Last(tGn->children);

    /*
     * Pass the buck to Make_HandleUse to apply the rule
     */
    (void)Make_HandleUse(gn, tGn);

    /*
     * Deal with wildcards and variables in any acquired sources
     */
    for (ln = Lst_Succ(ln); ln != NULL; ln = nln) {
	nln = Lst_Succ(ln);
	SuffExpandChildren(ln, tGn);
    }

    /*
     * Keep track of another parent to which this beast is transformed so
     * the .IMPSRC variable can be set correctly for the parent.
     */
    (void)Lst_AtEnd(sGn->iParents, tGn);

    return(TRUE);
}