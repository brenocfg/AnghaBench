#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int type; char* name; int /*<<< orphan*/  commands; int /*<<< orphan*/  children; } ;
struct TYPE_10__ {int children; int /*<<< orphan*/  cp; TYPE_3__* node; struct TYPE_10__* parent; TYPE_1__* suff; int /*<<< orphan*/  pref; int /*<<< orphan*/  file; } ;
struct TYPE_9__ {int /*<<< orphan*/  refCount; int /*<<< orphan*/  parents; } ;
typedef  TYPE_1__ Suff ;
typedef  TYPE_2__ Src ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  TYPE_3__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Member (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Open (int /*<<< orphan*/ ) ; 
 int OP_OPTIONAL ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffSuffHasNameP ; 
 TYPE_2__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  sufflist ; 

__attribute__((used)) static Src *
SuffFindCmds(Src *targ, Lst slst)
{
    LstNode 	  	ln; 	/* General-purpose list node */
    GNode		*t, 	/* Target GNode */
	    	  	*s; 	/* Source GNode */
    int	    	  	prefLen;/* The length of the defined prefix */
    Suff    	  	*suff;	/* Suffix on matching beastie */
    Src	    	  	*ret;	/* Return value */
    char    	  	*cp;

    t = targ->node;
    (void)Lst_Open(t->children);
    prefLen = strlen(targ->pref);

    for (;;) {
	ln = Lst_Next(t->children);
	if (ln == NULL) {
	    Lst_Close(t->children);
	    return NULL;
	}
	s = (GNode *)Lst_Datum(ln);

	if (s->type & OP_OPTIONAL && Lst_IsEmpty(t->commands)) {
	    /*
	     * We haven't looked to see if .OPTIONAL files exist yet, so
	     * don't use one as the implicit source.
	     * This allows us to use .OPTIONAL in .depend files so make won't
	     * complain "don't know how to make xxx.h' when a dependent file
	     * has been moved/deleted.
	     */
	    continue;
	}

	cp = strrchr(s->name, '/');
	if (cp == NULL) {
	    cp = s->name;
	} else {
	    cp++;
	}
	if (strncmp(cp, targ->pref, prefLen) != 0)
	    continue;
	/*
	 * The node matches the prefix ok, see if it has a known
	 * suffix.
	 */
	ln = Lst_Find(sufflist, &cp[prefLen], SuffSuffHasNameP);
	if (ln == NULL)
	    continue;
	/*
	 * It even has a known suffix, see if there's a transformation
	 * defined between the node's suffix and the target's suffix.
	 *
	 * XXX: Handle multi-stage transformations here, too.
	 */
	suff = (Suff *)Lst_Datum(ln);

	if (Lst_Member(suff->parents, targ->suff) != NULL)
	    break;
    }

    /*
     * Hot Damn! Create a new Src structure to describe
     * this transformation (making sure to duplicate the
     * source node's name so Suff_FindDeps can free it
     * again (ick)), and return the new structure.
     */
    ret = bmake_malloc(sizeof(Src));
    ret->file = bmake_strdup(s->name);
    ret->pref = targ->pref;
    ret->suff = suff;
    suff->refCount++;
    ret->parent = targ;
    ret->node = s;
    ret->children = 0;
    targ->children += 1;
#ifdef DEBUG_SRC
    ret->cp = Lst_Init(FALSE);
    fprintf(debug_file, "3 add %p %p\n", targ, ret);
    Lst_AtEnd(targ->cp, ret);
#endif
    Lst_AtEnd(slst, ret);
    if (DEBUG(SUFF)) {
	fprintf(debug_file, "\tusing existing source %s\n", s->name);
    }
    return (ret);
}