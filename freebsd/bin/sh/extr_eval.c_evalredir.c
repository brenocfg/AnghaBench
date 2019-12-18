#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  n; int /*<<< orphan*/  redirect; } ;
union node {TYPE_1__ nredir; } ;
struct jmploc {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int EXERROR ; 
 int /*<<< orphan*/  FORCEINTON ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  REDIR_PUSH ; 
 int /*<<< orphan*/  evaltree (int /*<<< orphan*/ ,int) ; 
 int exception ; 
 int /*<<< orphan*/  exitstatus ; 
 int /*<<< orphan*/  expredir (int /*<<< orphan*/ ) ; 
 struct jmploc* handler ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oexitstatus ; 
 int /*<<< orphan*/  popredir () ; 
 int /*<<< orphan*/  redirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evalredir(union node *n, int flags)
{
	struct jmploc jmploc;
	struct jmploc *savehandler;
	volatile int in_redirect = 1;

	oexitstatus = exitstatus;
	expredir(n->nredir.redirect);
	savehandler = handler;
	if (setjmp(jmploc.loc)) {
		int e;

		handler = savehandler;
		e = exception;
		popredir();
		if (e == EXERROR && in_redirect) {
			FORCEINTON;
			return;
		}
		longjmp(handler->loc, 1);
	} else {
		INTOFF;
		handler = &jmploc;
		redirect(n->nredir.redirect, REDIR_PUSH);
		in_redirect = 0;
		INTON;
		evaltree(n->nredir.n, flags);
	}
	INTOFF;
	handler = savehandler;
	popredir();
	INTON;
}