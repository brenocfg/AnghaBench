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
struct TYPE_3__ {int ls_event; scalar_t__ ls_count; scalar_t__ ls_lock; scalar_t__ ls_caller; scalar_t__* ls_stack; scalar_t__ ls_next; scalar_t__ ls_time; } ;
typedef  TYPE_1__ lsrec_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LS_MAX_EVENTS ; 
 int LS_STACK (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 char* format_symbol (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int g_nrecs_used ; 
 int /*<<< orphan*/  g_pflag ; 
 int g_recsize ; 

__attribute__((used)) static void
report_trace(FILE *out, lsrec_t **sort_buf)
{
	lsrec_t *lsp;
	int i, fr;
	int rectype;
	char buf[256], buf2[256];

	rectype = g_recsize;

	if (!g_pflag) {
		(void) fprintf(out, "%5s  %7s  %11s  %-24s  %-24s\n",
		    "Event", "Time", "Owner", "Lock", "Caller");
		(void) fprintf(out, "---------------------------------"
		    "----------------------------------------------\n");
	}

	for (i = 0; i < g_nrecs_used; i++) {

		lsp = sort_buf[i];

		if (lsp->ls_event >= LS_MAX_EVENTS || lsp->ls_count == 0)
			continue;

		(void) fprintf(out, "%2d  %10llu  %11p  %-24s  %-24s\n",
		    lsp->ls_event, (unsigned long long)lsp->ls_time,
		    (void *)lsp->ls_next,
#ifdef illumos
		    format_symbol(buf, lsp->ls_lock, 0),
#else
		    lsp->ls_lock,
#endif
		    format_symbol(buf2, lsp->ls_caller, 0));

		if (rectype <= LS_STACK(0))
			continue;

		/*
		 * If we went a few frames below the caller, ignore them
		 */
		for (fr = 3; fr > 0; fr--)
			if (lsp->ls_stack[fr] == lsp->ls_caller)
				break;

		while (rectype > LS_STACK(fr) && lsp->ls_stack[fr] != 0) {
			(void) fprintf(out, "%53s  %-24s\n", "",
			    format_symbol(buf, lsp->ls_stack[fr], 0));
			fr++;
		}
		(void) fprintf(out, "\n");
	}

	(void) fflush(out);
}