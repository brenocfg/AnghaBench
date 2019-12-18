#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ action_code; int suppressed; int number; size_t symbol; struct TYPE_3__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 scalar_t__ REDUCE ; 
 scalar_t__ backtrack ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_reductions(action *p, int defred2)
{
    int k, anyreds;
    action *q;

    anyreds = 0;
    for (q = p; q; q = q->next)
    {
	if (q->action_code == REDUCE && q->suppressed < 2)
	{
	    anyreds = 1;
	    break;
	}
    }

    if (anyreds == 0)
	fprintf(verbose_file, "\t.  error\n");
    else
    {
	for (; p; p = p->next)
	{
	    if (p->action_code == REDUCE && p->number != defred2)
	    {
		k = p->number - 2;
		if (p->suppressed == 0)
		    fprintf(verbose_file, "\t%s  reduce %d\n",
			    symbol_name[p->symbol], k);
#if defined(YYBTYACC)
		if (backtrack && p->suppressed == 1)
		    fprintf(verbose_file, "\t%s  [trial] reduce %d\n",
			    symbol_name[p->symbol], k);
#endif
	    }
	}

	if (defred2 > 0)
	    fprintf(verbose_file, "\t.  reduce %d\n", defred2 - 2);
    }
}