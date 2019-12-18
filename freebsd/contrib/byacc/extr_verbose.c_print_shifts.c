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
struct TYPE_3__ {int suppressed; scalar_t__ action_code; size_t symbol; int number; struct TYPE_3__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 scalar_t__ SHIFT ; 
 scalar_t__ backtrack ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_shifts(action *p)
{
    int count;
    action *q;

    count = 0;
    for (q = p; q; q = q->next)
    {
	if (q->suppressed < 2 && q->action_code == SHIFT)
	    ++count;
    }

    if (count > 0)
    {
	for (; p; p = p->next)
	{
	    if (p->action_code == SHIFT && p->suppressed == 0)
		fprintf(verbose_file, "\t%s  shift %d\n",
			symbol_name[p->symbol], p->number);
#if defined(YYBTYACC)
	    if (backtrack && p->action_code == SHIFT && p->suppressed == 1)
		fprintf(verbose_file, "\t%s  [trial] shift %d\n",
			symbol_name[p->symbol], p->number);
#endif
	}
    }
}