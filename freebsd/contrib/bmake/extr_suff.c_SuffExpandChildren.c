#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int type; char* name; int /*<<< orphan*/  parents; int /*<<< orphan*/  children; int /*<<< orphan*/  unmade; int /*<<< orphan*/  order_succ; int /*<<< orphan*/  order_pred; } ;
typedef  int /*<<< orphan*/  LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Arch_ParseArchive (char**,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_InsertBefore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_Prev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OP_ARCHV ; 
 int OP_WAIT ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffExpandWildcards (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TARG_CREATE ; 
 TYPE_1__* Targ_FindNode (char*,int /*<<< orphan*/ ) ; 
 int VARF_UNDEFERR ; 
 int VARF_WANTRES ; 
 char* Var_Parse (char*,TYPE_1__*,int,int*,void**) ; 
 char* Var_Subst (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* var_Error ; 

__attribute__((used)) static void
SuffExpandChildren(LstNode cln, GNode *pgn)
{
    GNode   	*cgn = (GNode *)Lst_Datum(cln);
    GNode	*gn;	    /* New source 8) */
    char	*cp;	    /* Expanded value */

    if (!Lst_IsEmpty(cgn->order_pred) || !Lst_IsEmpty(cgn->order_succ))
	/* It is all too hard to process the result of .ORDER */
	return;

    if (cgn->type & OP_WAIT)
	/* Ignore these (& OP_PHONY ?) */
	return;

    /*
     * First do variable expansion -- this takes precedence over
     * wildcard expansion. If the result contains wildcards, they'll be gotten
     * to later since the resulting words are tacked on to the end of
     * the children list.
     */
    if (strchr(cgn->name, '$') == NULL) {
	SuffExpandWildcards(cln, pgn);
	return;
    }

    if (DEBUG(SUFF)) {
	fprintf(debug_file, "Expanding \"%s\"...", cgn->name);
    }
    cp = Var_Subst(NULL, cgn->name, pgn, VARF_UNDEFERR|VARF_WANTRES);

    if (cp != NULL) {
	Lst	    members = Lst_Init(FALSE);

	if (cgn->type & OP_ARCHV) {
	    /*
	     * Node was an archive(member) target, so we want to call
	     * on the Arch module to find the nodes for us, expanding
	     * variables in the parent's context.
	     */
	    char	*sacrifice = cp;

	    (void)Arch_ParseArchive(&sacrifice, members, pgn);
	} else {
	    /*
	     * Break the result into a vector of strings whose nodes
	     * we can find, then add those nodes to the members list.
	     * Unfortunately, we can't use brk_string b/c it
	     * doesn't understand about variable specifications with
	     * spaces in them...
	     */
	    char	    *start;
	    char	    *initcp = cp;   /* For freeing... */

	    for (start = cp; *start == ' ' || *start == '\t'; start++)
		continue;
	    for (cp = start; *cp != '\0'; cp++) {
		if (*cp == ' ' || *cp == '\t') {
		    /*
		     * White-space -- terminate element, find the node,
		     * add it, skip any further spaces.
		     */
		    *cp++ = '\0';
		    gn = Targ_FindNode(start, TARG_CREATE);
		    (void)Lst_AtEnd(members, gn);
		    while (*cp == ' ' || *cp == '\t') {
			cp++;
		    }
		    /*
		     * Adjust cp for increment at start of loop, but
		     * set start to first non-space.
		     */
		    start = cp--;
		} else if (*cp == '$') {
		    /*
		     * Start of a variable spec -- contact variable module
		     * to find the end so we can skip over it.
		     */
		    char	*junk;
		    int 	len;
		    void	*freeIt;

		    junk = Var_Parse(cp, pgn, VARF_UNDEFERR|VARF_WANTRES,
			&len, &freeIt);
		    if (junk != var_Error) {
			cp += len - 1;
		    }

		    free(freeIt);
		} else if (*cp == '\\' && cp[1] != '\0') {
		    /*
		     * Escaped something -- skip over it
		     */
		    cp++;
		}
	    }

	    if (cp != start) {
		/*
		 * Stuff left over -- add it to the list too
		 */
		gn = Targ_FindNode(start, TARG_CREATE);
		(void)Lst_AtEnd(members, gn);
	    }
	    /*
	     * Point cp back at the beginning again so the variable value
	     * can be freed.
	     */
	    cp = initcp;
	}

	/*
	 * Add all elements of the members list to the parent node.
	 */
	while(!Lst_IsEmpty(members)) {
	    gn = (GNode *)Lst_DeQueue(members);

	    if (DEBUG(SUFF)) {
		fprintf(debug_file, "%s...", gn->name);
	    }
	    /* Add gn to the parents child list before the original child */
	    (void)Lst_InsertBefore(pgn->children, cln, gn);
	    (void)Lst_AtEnd(gn->parents, pgn);
	    pgn->unmade++;
	    /* Expand wildcards on new node */
	    SuffExpandWildcards(Lst_Prev(cln), pgn);
	}
	Lst_Destroy(members, NULL);

	/*
	 * Free the result
	 */
	free(cp);
    }
    if (DEBUG(SUFF)) {
	fprintf(debug_file, "\n");
    }

    /*
     * Now the source is expanded, remove it from the list of children to
     * keep it from being processed.
     */
    pgn->unmade--;
    Lst_Remove(pgn->children, cln);
    Lst_Remove(cgn->parents, Lst_Member(cgn->parents, pgn));
}