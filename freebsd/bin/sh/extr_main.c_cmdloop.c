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
typedef  union node {int dummy; } node ;
struct stackmark {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Iflag ; 
 union node* NEOF ; 
 int /*<<< orphan*/  SHOWJOBS_DEFAULT ; 
 scalar_t__ SKIPRETURN ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  chkmail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dotrap () ; 
 scalar_t__ evalskip ; 
 int /*<<< orphan*/  evaltree (union node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ *) ; 
 scalar_t__ iflag ; 
 int job_warning ; 
 scalar_t__ nflag ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 int /*<<< orphan*/  output ; 
 union node* parsecmd (int) ; 
 scalar_t__ pendingsig ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  showjobs (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoppedjobs () ; 

__attribute__((used)) static void
cmdloop(int top)
{
	union node *n;
	struct stackmark smark;
	int inter;
	int numeof = 0;

	TRACE(("cmdloop(%d) called\n", top));
	setstackmark(&smark);
	for (;;) {
		if (pendingsig)
			dotrap();
		inter = 0;
		if (iflag && top) {
			inter++;
			showjobs(1, SHOWJOBS_DEFAULT);
			chkmail(0);
			flushout(&output);
		}
		n = parsecmd(inter);
		/* showtree(n); DEBUG */
		if (n == NEOF) {
			if (!top || numeof >= 50)
				break;
			if (!stoppedjobs()) {
				if (!Iflag)
					break;
				out2fmt_flush("\nUse \"exit\" to leave shell.\n");
			}
			numeof++;
		} else if (n != NULL && nflag == 0) {
			job_warning = (job_warning == 2) ? 1 : 0;
			numeof = 0;
			evaltree(n, 0);
		}
		popstackmark(&smark);
		setstackmark(&smark);
		if (evalskip != 0) {
			if (evalskip == SKIPRETURN)
				evalskip = 0;
			break;
		}
	}
	popstackmark(&smark);
}