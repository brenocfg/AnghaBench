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
struct TYPE_3__ {int nitems; int* items; } ;
typedef  TYPE_1__ core ;
typedef  size_t Value_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 size_t* ritem ; 
 size_t* rlhs ; 
 int* rrhs ; 
 TYPE_1__** state_table ; 
 char** symbol_name ; 
 int /*<<< orphan*/  verbose_file ; 

__attribute__((used)) static void
print_core(int state)
{
    int i;
    int k;
    int rule;
    core *statep;
    Value_t *sp;
    Value_t *sp1;

    statep = state_table[state];
    k = statep->nitems;

    for (i = 0; i < k; i++)
    {
	sp1 = sp = ritem + statep->items[i];

	while (*sp >= 0)
	    ++sp;
	rule = -(*sp);
	fprintf(verbose_file, "\t%s : ", symbol_name[rlhs[rule]]);

	for (sp = ritem + rrhs[rule]; sp < sp1; sp++)
	    fprintf(verbose_file, "%s ", symbol_name[*sp]);

	putc('.', verbose_file);

	while (*sp >= 0)
	{
	    fprintf(verbose_file, " %s", symbol_name[*sp]);
	    sp++;
	}
	fprintf(verbose_file, "  (%d)\n", -2 - *sp);
    }
}