#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int type; char* name; int /*<<< orphan*/  children; } ;
struct TYPE_11__ {TYPE_4__** gn; scalar_t__ r; TYPE_1__* s; } ;
struct TYPE_10__ {char* name; int /*<<< orphan*/  parents; int /*<<< orphan*/  children; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Suff ;
typedef  TYPE_3__ GNodeSuff ;
typedef  TYPE_4__ GNode ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 int OP_NOTARGET ; 
 unsigned int OP_TRANSFORM ; 
 int /*<<< orphan*/  SUFF ; 
 int /*<<< orphan*/  SuffInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SuffParseTransform (char*,TYPE_2__**,TYPE_2__**) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Targ_SetMain (TYPE_4__*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SuffScanTargets(void *targetp, void *gsp)
{
    GNode   	*target = (GNode *)targetp;
    GNodeSuff	*gs = (GNodeSuff *)gsp;
    Suff	*s, *t;
    char 	*ptr;

    if (*gs->gn == NULL && gs->r && (target->type & OP_NOTARGET) == 0) {
	*gs->gn = target;
	Targ_SetMain(target);
	return 1;
    }

    if ((unsigned int)target->type == OP_TRANSFORM)
	return 0;

    if ((ptr = strstr(target->name, gs->s->name)) == NULL ||
	ptr == target->name)
	return 0;

    if (SuffParseTransform(target->name, &s, &t)) {
	if (*gs->gn == target) {
	    gs->r = TRUE;
	    *gs->gn = NULL;
	    Targ_SetMain(NULL);
	}
	Lst_Destroy(target->children, NULL);
	target->children = Lst_Init(FALSE);
	target->type = OP_TRANSFORM;
	/*
	 * link the two together in the proper relationship and order
	 */
	if (DEBUG(SUFF)) {
	    fprintf(debug_file, "defining transformation from `%s' to `%s'\n",
		s->name, t->name);
	}
	SuffInsert(t->children, s);
	SuffInsert(s->parents, t);
    }
    return 0;
}