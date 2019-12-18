#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  type; void* children; void* commands; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  parents; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ Suff ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_2__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Destroy (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_TRANSFORM ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffGNHasNameP ; 
 int /*<<< orphan*/  SuffInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SuffParseTransform (char*,TYPE_1__**,TYPE_1__**) ; 
 TYPE_2__* Targ_NewGN (char*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  transforms ; 

GNode *
Suff_AddTransform(char *line)
{
    GNode         *gn;		/* GNode of transformation rule */
    Suff          *s,		/* source suffix */
                  *t;		/* target suffix */
    LstNode 	  ln;	    	/* Node for existing transformation */

    ln = Lst_Find(transforms, line, SuffGNHasNameP);
    if (ln == NULL) {
	/*
	 * Make a new graph node for the transformation. It will be filled in
	 * by the Parse module.
	 */
	gn = Targ_NewGN(line);
	(void)Lst_AtEnd(transforms, gn);
    } else {
	/*
	 * New specification for transformation rule. Just nuke the old list
	 * of commands so they can be filled in again... We don't actually
	 * free the commands themselves, because a given command can be
	 * attached to several different transformations.
	 */
	gn = (GNode *)Lst_Datum(ln);
	Lst_Destroy(gn->commands, NULL);
	Lst_Destroy(gn->children, NULL);
	gn->commands = Lst_Init(FALSE);
	gn->children = Lst_Init(FALSE);
    }

    gn->type = OP_TRANSFORM;

    (void)SuffParseTransform(line, &s, &t);

    /*
     * link the two together in the proper relationship and order
     */
    if (DEBUG(SUFF)) {
	fprintf(debug_file, "defining transformation from `%s' to `%s'\n",
		s->name, t->name);
    }
    SuffInsert(t->children, s);
    SuffInsert(s->parents, t);

    return (gn);
}