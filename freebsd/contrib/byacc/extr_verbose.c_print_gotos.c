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
struct TYPE_3__ {int* shift; int nshifts; } ;
typedef  TYPE_1__ shifts ;
typedef  int Value_t ;

/* Variables and functions */
 scalar_t__ ISVAR (int) ; 
 int* accessing_symbol ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 TYPE_1__** shift_table ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_gotos(int stateno)
{
    int i, k;
    int as;
    Value_t *to_state2;
    shifts *sp;

    putc('\n', verbose_file);
    sp = shift_table[stateno];
    to_state2 = sp->shift;
    for (i = 0; i < sp->nshifts; ++i)
    {
	k = to_state2[i];
	as = accessing_symbol[k];
	if (ISVAR(as))
	    fprintf(verbose_file, "\t%s  goto %d\n", symbol_name[as], k);
    }
}