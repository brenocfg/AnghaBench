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
struct TYPE_3__ {int suppressed; int symbol; int number; int action_code; struct TYPE_3__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 int REDUCE ; 
 int SHIFT ; 
 int final_state ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 TYPE_1__** parser ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_conflicts(int state)
{
    int symbol, act, number;
    action *p;

    act = 0;			/* not shift/reduce... */
    number = -1;
    symbol = -1;
    for (p = parser[state]; p; p = p->next)
    {
	if (p->suppressed == 2)
	    continue;

	if (p->symbol != symbol)
	{
	    symbol = p->symbol;
	    number = p->number;
	    if (p->action_code == SHIFT)
		act = SHIFT;
	    else
		act = REDUCE;
	}
	else if (p->suppressed == 1)
	{
	    if (state == final_state && symbol == 0)
	    {
		fprintf(verbose_file, "%d: shift/reduce conflict \
(accept, reduce %d) on $end\n", state, p->number - 2);
	    }
	    else
	    {
		if (act == SHIFT)
		{
		    fprintf(verbose_file, "%d: shift/reduce conflict \
(shift %d, reduce %d) on %s\n", state, number, p->number - 2,
			    symbol_name[symbol]);
		}
		else
		{
		    fprintf(verbose_file, "%d: reduce/reduce conflict \
(reduce %d, reduce %d) on %s\n", state, number - 2, p->number - 2,
			    symbol_name[symbol]);
		}
	    }
	}
    }
}