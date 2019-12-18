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
struct TYPE_3__ {int nitems; int* items; int number; struct TYPE_3__* link; } ;
typedef  TYPE_1__ core ;
typedef  int Value_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int** kernel_base ; 
 int** kernel_end ; 
 void* new_state (int) ; 
 int nitems ; 
 TYPE_1__** state_set ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static Value_t
get_state(int symbol)
{
    int key;
    Value_t *isp1;
    Value_t *isp2;
    Value_t *iend;
    core *sp;
    int found;
    int n;

#ifdef	TRACE
    fprintf(stderr, "Entering get_state(%d)\n", symbol);
#endif

    isp1 = kernel_base[symbol];
    iend = kernel_end[symbol];
    n = (int)(iend - isp1);

    key = *isp1;
    assert(0 <= key && key < nitems);
    sp = state_set[key];
    if (sp)
    {
	found = 0;
	while (!found)
	{
	    if (sp->nitems == n)
	    {
		found = 1;
		isp1 = kernel_base[symbol];
		isp2 = sp->items;

		while (found && isp1 < iend)
		{
		    if (*isp1++ != *isp2++)
			found = 0;
		}
	    }

	    if (!found)
	    {
		if (sp->link)
		{
		    sp = sp->link;
		}
		else
		{
		    sp = sp->link = new_state(symbol);
		    found = 1;
		}
	    }
	}
    }
    else
    {
	state_set[key] = sp = new_state(symbol);
    }

    return (sp->number);
}