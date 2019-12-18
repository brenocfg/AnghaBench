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
struct TYPE_3__ {size_t number; int /*<<< orphan*/  accessing_symbol; struct TYPE_3__* next; } ;
typedef  TYPE_1__ core ;

/* Variables and functions */
 int /*<<< orphan*/ * NEW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Value_t ; 
 int /*<<< orphan*/ * accessing_symbol ; 
 TYPE_1__* first_state ; 
 int /*<<< orphan*/  nstates ; 

__attribute__((used)) static void
set_accessing_symbol(void)
{
    core *sp;

    accessing_symbol = NEW2(nstates, Value_t);
    for (sp = first_state; sp; sp = sp->next)
	accessing_symbol[sp->number] = sp->accessing_symbol;
}