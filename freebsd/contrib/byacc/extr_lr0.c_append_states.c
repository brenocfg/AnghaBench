#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Value_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_state (scalar_t__) ; 
 int nshifts ; 
 scalar_t__* shift_symbol ; 
 int /*<<< orphan*/ * shiftset ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
append_states(void)
{
    int i;
    int j;
    Value_t symbol;

#ifdef	TRACE
    fprintf(stderr, "Entering append_states()\n");
#endif
    for (i = 1; i < nshifts; i++)
    {
	symbol = shift_symbol[i];
	j = i;
	while (j > 0 && shift_symbol[j - 1] > symbol)
	{
	    shift_symbol[j] = shift_symbol[j - 1];
	    j--;
	}
	shift_symbol[j] = symbol;
    }

    for (i = 0; i < nshifts; i++)
    {
	symbol = shift_symbol[i];
	shiftset[i] = get_state(symbol);
    }
}