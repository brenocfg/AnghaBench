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
 int EV_EXIT ; 
 int /*<<< orphan*/  EXEXIT ; 
 union node* NEOF ; 
 scalar_t__ evalskip ; 
 int /*<<< orphan*/  evaltree (union node*,int) ; 
 scalar_t__ exitstatus ; 
 int /*<<< orphan*/  exraise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nflag ; 
 union node* parsecmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popfile () ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 scalar_t__ preadateof () ; 
 int /*<<< orphan*/  setinputstring (char const*,int) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 

void
evalstring(const char *s, int flags)
{
	union node *n;
	struct stackmark smark;
	int flags_exit;
	int any;

	flags_exit = flags & EV_EXIT;
	flags &= ~EV_EXIT;
	any = 0;
	setstackmark(&smark);
	setinputstring(s, 1);
	while ((n = parsecmd(0)) != NEOF) {
		if (n != NULL && !nflag) {
			if (flags_exit && preadateof())
				evaltree(n, flags | EV_EXIT);
			else
				evaltree(n, flags);
			any = 1;
			if (evalskip)
				break;
		}
		popstackmark(&smark);
		setstackmark(&smark);
	}
	popfile();
	popstackmark(&smark);
	if (!any)
		exitstatus = 0;
	if (flags_exit)
		exraise(EXEXIT);
}