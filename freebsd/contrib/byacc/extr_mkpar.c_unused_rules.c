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
struct TYPE_4__ {scalar_t__ action_code; size_t number; struct TYPE_4__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 scalar_t__ MaySuppress (TYPE_1__*) ; 
 int /*<<< orphan*/  NO_SPACE (int*) ; 
 scalar_t__ REDUCE ; 
 int* TMALLOC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Value_t ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* myname ; 
 int nrules ; 
 int nstates ; 
 int nunused ; 
 TYPE_1__** parser ; 
 int* rules_used ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
unused_rules(void)
{
    int i;
    action *p;

    rules_used = TMALLOC(Value_t, nrules);
    NO_SPACE(rules_used);

    for (i = 0; i < nrules; ++i)
	rules_used[i] = 0;

    for (i = 0; i < nstates; ++i)
    {
	for (p = parser[i]; p; p = p->next)
	{
	    if ((p->action_code == REDUCE) && MaySuppress(p))
		rules_used[p->number] = 1;
	}
    }

    nunused = 0;
    for (i = 3; i < nrules; ++i)
	if (!rules_used[i])
	    ++nunused;

    if (nunused)
    {
	if (nunused == 1)
	    fprintf(stderr, "%s: 1 rule never reduced\n", myname);
	else
	    fprintf(stderr, "%s: %d rules never reduced\n", myname, nunused);
    }
}