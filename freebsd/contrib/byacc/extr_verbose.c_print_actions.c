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
struct TYPE_3__ {int nshifts; size_t* shift; } ;
typedef  TYPE_1__ shifts ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 scalar_t__ ISVAR (int) ; 
 int* accessing_symbol ; 
 int /*<<< orphan*/ * defred ; 
 int final_state ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** parser ; 
 int /*<<< orphan*/  print_gotos (int) ; 
 int /*<<< orphan*/  print_reductions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_shifts (int /*<<< orphan*/ *) ; 
 TYPE_1__** shift_table ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_actions(int stateno)
{
    action *p;
    shifts *sp;
    int as;

    if (stateno == final_state)
	fprintf(verbose_file, "\t$end  accept\n");

    p = parser[stateno];
    if (p)
    {
	print_shifts(p);
	print_reductions(p, defred[stateno]);
    }

    sp = shift_table[stateno];
    if (sp && sp->nshifts > 0)
    {
	as = accessing_symbol[sp->shift[sp->nshifts - 1]];
	if (ISVAR(as))
	    print_gotos(stateno);
    }
}