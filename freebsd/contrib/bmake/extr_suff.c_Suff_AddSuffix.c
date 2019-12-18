#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int refCount; int /*<<< orphan*/  r; struct TYPE_6__* s; int /*<<< orphan*/ ** gn; scalar_t__ flags; scalar_t__ sNum; void* ref; void* parents; void* children; void* searchPath; int /*<<< orphan*/  name; int /*<<< orphan*/  nameLen; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_1__ GNodeSuff ;
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SuffRebuildGraph ; 
 int /*<<< orphan*/  SuffScanTargets ; 
 int /*<<< orphan*/  SuffSuffHasNameP ; 
 int /*<<< orphan*/  Targ_List () ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char*) ; 
 int /*<<< orphan*/  sNum ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sufflist ; 
 int /*<<< orphan*/  transforms ; 

void
Suff_AddSuffix(char *str, GNode **gn)
{
    Suff          *s;	    /* new suffix descriptor */
    LstNode 	  ln;
    GNodeSuff	  gs;

    ln = Lst_Find(sufflist, str, SuffSuffHasNameP);
    if (ln == NULL) {
	s = bmake_malloc(sizeof(Suff));

	s->name =   	bmake_strdup(str);
	s->nameLen = 	strlen(s->name);
	s->searchPath = Lst_Init(FALSE);
	s->children = 	Lst_Init(FALSE);
	s->parents = 	Lst_Init(FALSE);
	s->ref = 	Lst_Init(FALSE);
	s->sNum =   	sNum++;
	s->flags =  	0;
	s->refCount =	1;

	(void)Lst_AtEnd(sufflist, s);
	/*
	 * We also look at our existing targets list to see if adding
	 * this suffix will make one of our current targets mutate into
	 * a suffix rule. This is ugly, but other makes treat all targets
	 * that start with a . as suffix rules.
	 */
	gs.gn = gn;
	gs.s  = s;
	gs.r  = FALSE;
	Lst_ForEach(Targ_List(), SuffScanTargets, &gs);
	/*
	 * Look for any existing transformations from or to this suffix.
	 * XXX: Only do this after a Suff_ClearSuffixes?
	 */
	Lst_ForEach(transforms, SuffRebuildGraph, s);
    }
}