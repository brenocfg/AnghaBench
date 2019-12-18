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

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ RRtotal ; 
 scalar_t__ SRtotal ; 
 int /*<<< orphan*/  TMALLOC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Value_t ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_conflicts () ; 
 int /*<<< orphan*/  log_unused () ; 
 int nrules ; 
 int nstates ; 
 int nsyms ; 
 int ntokens ; 
 int /*<<< orphan*/  null_rules ; 
 scalar_t__ nunused ; 
 int nvars ; 
 int /*<<< orphan*/  print_state (int) ; 
 char** symbol_name ; 
 int* symbol_value ; 
 int /*<<< orphan*/  verbose_file ; 
 int /*<<< orphan*/  vflag ; 

void
verbose(void)
{
    int i;

    if (!vflag)
	return;

    null_rules = TMALLOC(Value_t, nrules);
    NO_SPACE(null_rules);

    fprintf(verbose_file, "\f\n");
    for (i = 0; i < nstates; i++)
	print_state(i);
    FREE(null_rules);

    if (nunused)
	log_unused();
    if (SRtotal || RRtotal)
	log_conflicts();

    fprintf(verbose_file, "\n\n%d terminals, %d nonterminals\n", ntokens,
	    nvars);
    fprintf(verbose_file, "%d grammar rules, %d states\n", nrules - 2, nstates);
#if defined(YYBTYACC)
    {				/* print out the grammar symbol # and parser internal symbol # for each
				   symbol as an aide to writing the implementation for YYDESTRUCT_CALL()
				   and YYSTYPE_TOSTRING() */
	int maxtok = 0;

	fputs("\ngrammar parser grammar\n", verbose_file);
	fputs("symbol# value# symbol\n", verbose_file);
	for (i = 0; i < ntokens; ++i)
	{
	    fprintf(verbose_file, " %5d  %5d  %s\n",
		    i, symbol_value[i], symbol_name[i]);
	    if (symbol_value[i] > maxtok)
		maxtok = symbol_value[i];
	}
	for (i = ntokens; i < nsyms; ++i)
	    fprintf(verbose_file, " %5d  %5d  %s\n",
		    i, (maxtok + 1) + symbol_value[i] + 1, symbol_name[i]);
    }
#endif
}