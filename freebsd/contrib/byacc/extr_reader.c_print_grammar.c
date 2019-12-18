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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int nrules ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 size_t* ritem ; 
 size_t* rlhs ; 
 int strlen (char*) ; 
 char** symbol_name ; 
 int /*<<< orphan*/ * verbose_file ; 
 int /*<<< orphan*/  vflag ; 

__attribute__((used)) static void
print_grammar(void)
{
    int i, k;
    size_t j, spacing = 0;
    FILE *f = verbose_file;

    if (!vflag)
	return;

    k = 1;
    for (i = 2; i < nrules; ++i)
    {
	if (rlhs[i] != rlhs[i - 1])
	{
	    if (i != 2)
		fprintf(f, "\n");
	    fprintf(f, "%4d  %s :", i - 2, symbol_name[rlhs[i]]);
	    spacing = strlen(symbol_name[rlhs[i]]) + 1;
	}
	else
	{
	    fprintf(f, "%4d  ", i - 2);
	    j = spacing;
	    while (j-- != 0)
		putc(' ', f);
	    putc('|', f);
	}

	while (ritem[k] >= 0)
	{
	    fprintf(f, " %s", symbol_name[ritem[k]]);
	    ++k;
	}
	++k;
	putc('\n', f);
    }
}