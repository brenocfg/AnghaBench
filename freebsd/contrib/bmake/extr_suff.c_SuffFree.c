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
struct TYPE_6__ {struct TYPE_6__* name; int /*<<< orphan*/  searchPath; int /*<<< orphan*/  parents; int /*<<< orphan*/  children; int /*<<< orphan*/  ref; scalar_t__ refCount; } ;
typedef  TYPE_1__ Suff ;

/* Variables and functions */
 int /*<<< orphan*/ * Dir_Destroy ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Punt (char*,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* emptySuff ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* suffNull ; 

__attribute__((used)) static void
SuffFree(void *sp)
{
    Suff           *s = (Suff *)sp;

    if (s == suffNull)
	suffNull = NULL;

    if (s == emptySuff)
	emptySuff = NULL;

#ifdef notdef
    /* We don't delete suffixes in order, so we cannot use this */
    if (s->refCount)
	Punt("Internal error deleting suffix `%s' with refcount = %d", s->name,
	    s->refCount);
#endif

    Lst_Destroy(s->ref, NULL);
    Lst_Destroy(s->children, NULL);
    Lst_Destroy(s->parents, NULL);
    Lst_Destroy(s->searchPath, Dir_Destroy);

    free(s->name);
    free(s);
}