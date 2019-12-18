#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {union node* redirect; union node* args; } ;
struct TYPE_5__ {char* text; union node* next; } ;
struct TYPE_4__ {union node* next; } ;
union node {TYPE_3__ ncmd; int /*<<< orphan*/  type; TYPE_2__ narg; TYPE_1__ nfile; } ;
struct ncmd {int dummy; } ;

/* Variables and functions */
 int CHKALIAS ; 
 int /*<<< orphan*/  NCMD ; 
 int /*<<< orphan*/  NDEFUN ; 
 scalar_t__ TLP ; 
 scalar_t__ TREDIR ; 
 int /*<<< orphan*/  TRP ; 
 scalar_t__ TWORD ; 
 int checkkwd ; 
 union node* command () ; 
 int /*<<< orphan*/  consumetoken (int /*<<< orphan*/ ) ; 
 scalar_t__ find_builtin (char*,int*) ; 
 scalar_t__ funclinno ; 
 int /*<<< orphan*/  isassignment (int /*<<< orphan*/ ) ; 
 scalar_t__ lasttoken ; 
 union node* makename () ; 
 int /*<<< orphan*/  noexpand (char*) ; 
 int /*<<< orphan*/  parsefname () ; 
 scalar_t__ plinno ; 
 scalar_t__ quoteflag ; 
 scalar_t__ readtoken () ; 
 union node* redirnode ; 
 int /*<<< orphan*/  rmescapes (char*) ; 
 scalar_t__ stalloc (int) ; 
 scalar_t__ strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  synerror (char*) ; 
 int /*<<< orphan*/  tokpushback ; 
 int /*<<< orphan*/  wordtext ; 

__attribute__((used)) static union node *
simplecmd(union node **rpp, union node *redir)
{
	union node *args, **app;
	union node **orig_rpp = rpp;
	union node *n = NULL;
	int special;
	int savecheckkwd;

	/* If we don't have any redirections already, then we must reset */
	/* rpp to be the address of the local redir variable.  */
	if (redir == NULL)
		rpp = &redir;

	args = NULL;
	app = &args;
	/*
	 * We save the incoming value, because we need this for shell
	 * functions.  There can not be a redirect or an argument between
	 * the function name and the open parenthesis.
	 */
	orig_rpp = rpp;

	savecheckkwd = CHKALIAS;

	for (;;) {
		checkkwd = savecheckkwd;
		if (readtoken() == TWORD) {
			n = makename();
			*app = n;
			app = &n->narg.next;
			if (savecheckkwd != 0 && !isassignment(wordtext))
				savecheckkwd = 0;
		} else if (lasttoken == TREDIR) {
			*rpp = n = redirnode;
			rpp = &n->nfile.next;
			parsefname();	/* read name of redirection file */
		} else if (lasttoken == TLP && app == &args->narg.next
					    && rpp == orig_rpp) {
			/* We have a function */
			consumetoken(TRP);
			funclinno = plinno;
			/*
			 * - Require plain text.
			 * - Functions with '/' cannot be called.
			 * - Reject name=().
			 * - Reject ksh extended glob patterns.
			 */
			if (!noexpand(n->narg.text) || quoteflag ||
			    strchr(n->narg.text, '/') ||
			    strchr("!%*+-=?@}~",
				n->narg.text[strlen(n->narg.text) - 1]))
				synerror("Bad function name");
			rmescapes(n->narg.text);
			if (find_builtin(n->narg.text, &special) >= 0 &&
			    special)
				synerror("Cannot override a special builtin with a function");
			n->type = NDEFUN;
			n->narg.next = command();
			funclinno = 0;
			return n;
		} else {
			tokpushback++;
			break;
		}
	}
	*app = NULL;
	*rpp = NULL;
	n = (union node *)stalloc(sizeof (struct ncmd));
	n->type = NCMD;
	n->ncmd.args = args;
	n->ncmd.redirect = redir;
	return n;
}