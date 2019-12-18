#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ class; int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bucket ;
struct TYPE_5__ {scalar_t__ class; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ TERM ; 
 scalar_t__ UNKNOWN ; 
 TYPE_1__* first_symbol ; 
 TYPE_2__* goal ; 
 int /*<<< orphan*/  undefined_goal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  undefined_symbol_warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_symbols(void)
{
    bucket *bp;

    if (goal->class == UNKNOWN)
	undefined_goal(goal->name);

    for (bp = first_symbol; bp; bp = bp->next)
    {
	if (bp->class == UNKNOWN)
	{
	    undefined_symbol_warning(bp->name);
	    bp->class = TERM;
	}
    }
}