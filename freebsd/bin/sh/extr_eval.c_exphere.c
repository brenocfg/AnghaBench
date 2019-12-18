#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* expdoc; int /*<<< orphan*/  doc; } ;
union node {TYPE_1__ nhere; } ;
struct localvar {int dummy; } ;
struct jmploc {int /*<<< orphan*/  loc; } ;
struct arglist {char** args; } ;
struct TYPE_4__ {unsigned char reset; } ;

/* Variables and functions */
 scalar_t__ EXERROR ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ exception ; 
 int /*<<< orphan*/  expandarg (int /*<<< orphan*/ ,struct arglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forcelocal ; 
 struct jmploc* handler ; 
 struct localvar* localvars ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poplocalvars () ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 TYPE_2__ shellparam ; 

__attribute__((used)) static void
exphere(union node *redir, struct arglist *fn)
{
	struct jmploc jmploc;
	struct jmploc *savehandler;
	struct localvar *savelocalvars;
	int need_longjmp = 0;
	unsigned char saveoptreset;

	redir->nhere.expdoc = "";
	savelocalvars = localvars;
	localvars = NULL;
	saveoptreset = shellparam.reset;
	forcelocal++;
	savehandler = handler;
	if (setjmp(jmploc.loc))
		need_longjmp = exception != EXERROR;
	else {
		handler = &jmploc;
		expandarg(redir->nhere.doc, fn, 0);
		redir->nhere.expdoc = fn->args[0];
		INTOFF;
	}
	handler = savehandler;
	forcelocal--;
	poplocalvars();
	localvars = savelocalvars;
	shellparam.reset = saveoptreset;
	if (need_longjmp)
		longjmp(handler->loc, 1);
	INTON;
}