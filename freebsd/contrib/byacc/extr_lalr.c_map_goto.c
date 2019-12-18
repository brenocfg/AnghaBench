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
typedef  int /*<<< orphan*/  Value_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* from_state ; 
 int* goto_map ; 

__attribute__((used)) static Value_t
map_goto(int state, int symbol)
{
    int high;
    int low;
    int middle;
    int s;

    low = goto_map[symbol];
    high = goto_map[symbol + 1];

    for (;;)
    {
	assert(low <= high);
	middle = (low + high) >> 1;
	s = from_state[middle];
	if (s == state)
	    return (Value_t)(middle);
	else if (s < state)
	    low = middle + 1;
	else
	    high = middle - 1;
    }
}