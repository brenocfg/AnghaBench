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
struct TYPE_3__ {scalar_t__ action_code; int suppressed; size_t number; struct TYPE_3__* next; } ;
typedef  TYPE_1__ action ;
typedef  size_t Value_t ;

/* Variables and functions */
 scalar_t__ REDUCE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t* null_rules ; 
 TYPE_1__** parser ; 
 size_t* rlhs ; 
 scalar_t__* rrhs ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_nulls(int state)
{
    action *p;
    Value_t i, j, k, nnulls;

    nnulls = 0;
    for (p = parser[state]; p; p = p->next)
    {
	if (p->action_code == REDUCE &&
	    (p->suppressed == 0 || p->suppressed == 1))
	{
	    i = p->number;
	    if (rrhs[i] + 1 == rrhs[i + 1])
	    {
		for (j = 0; j < nnulls && i > null_rules[j]; ++j)
		    continue;

		if (j == nnulls)
		{
		    ++nnulls;
		    null_rules[j] = i;
		}
		else if (i != null_rules[j])
		{
		    ++nnulls;
		    for (k = (Value_t)(nnulls - 1); k > j; --k)
			null_rules[k] = null_rules[k - 1];
		    null_rules[j] = i;
		}
	    }
	}
    }

    for (i = 0; i < nnulls; ++i)
    {
	j = null_rules[i];
	fprintf(verbose_file, "\t%s : .  (%d)\n", symbol_name[rlhs[j]],
		j - 2);
    }
    fprintf(verbose_file, "\n");
}