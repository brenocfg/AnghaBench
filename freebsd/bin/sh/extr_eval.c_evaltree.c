#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {union node* com; } ;
struct TYPE_9__ {int /*<<< orphan*/  next; int /*<<< orphan*/  text; } ;
struct TYPE_8__ {union node* next; union node* body; } ;
struct TYPE_7__ {union node* elsepart; union node* ifpart; union node* test; } ;
struct TYPE_6__ {union node* ch2; union node* ch1; } ;
union node {int type; TYPE_5__ nnot; TYPE_4__ narg; TYPE_3__ nclist; TYPE_2__ nif; TYPE_1__ nbinary; } ;
struct stackmark {int dummy; } ;
struct backcmd {int dummy; } ;

/* Variables and functions */
 int EV_EXIT ; 
 int EV_TESTED ; 
 int /*<<< orphan*/  EXEXIT ; 
#define  NAND 144 
#define  NBACKGND 143 
#define  NCASE 142 
#define  NCLIST 141 
#define  NCLISTFALLTHRU 140 
#define  NCMD 139 
#define  NDEFUN 138 
#define  NFOR 137 
#define  NIF 136 
#define  NNOT 135 
#define  NOR 134 
#define  NPIPE 133 
#define  NREDIR 132 
#define  NSEMI 131 
#define  NSUBSHELL 130 
#define  NUNTIL 129 
#define  NWHILE 128 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  defun (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int displayhist ; 
 int /*<<< orphan*/  dotrap () ; 
 scalar_t__ eflag ; 
 union node* evalcase (union node*) ; 
 int /*<<< orphan*/  evalcommand (union node*,int,struct backcmd*) ; 
 int /*<<< orphan*/  evalfor (union node*,int) ; 
 int /*<<< orphan*/  evalloop (union node*,int) ; 
 int /*<<< orphan*/  evalpipe (union node*) ; 
 int /*<<< orphan*/  evalredir (union node*,int) ; 
 int /*<<< orphan*/  evalskip ; 
 int /*<<< orphan*/  evalsubshell (union node*,int) ; 
 int /*<<< orphan*/  exitshell (scalar_t__) ; 
 scalar_t__ exitstatus ; 
 int /*<<< orphan*/  exraise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out1fmt (char*,int) ; 
 int /*<<< orphan*/  output ; 
 scalar_t__ pendingsig ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 

void
evaltree(union node *n, int flags)
{
	int do_etest;
	union node *next;
	struct stackmark smark;

	setstackmark(&smark);
	do_etest = 0;
	if (n == NULL) {
		TRACE(("evaltree(NULL) called\n"));
		exitstatus = 0;
		goto out;
	}
	do {
		next = NULL;
#ifndef NO_HISTORY
		displayhist = 1;	/* show history substitutions done with fc */
#endif
		TRACE(("evaltree(%p: %d) called\n", (void *)n, n->type));
		switch (n->type) {
		case NSEMI:
			evaltree(n->nbinary.ch1, flags & ~EV_EXIT);
			if (evalskip)
				goto out;
			next = n->nbinary.ch2;
			break;
		case NAND:
			evaltree(n->nbinary.ch1, EV_TESTED);
			if (evalskip || exitstatus != 0) {
				goto out;
			}
			next = n->nbinary.ch2;
			break;
		case NOR:
			evaltree(n->nbinary.ch1, EV_TESTED);
			if (evalskip || exitstatus == 0)
				goto out;
			next = n->nbinary.ch2;
			break;
		case NREDIR:
			evalredir(n, flags);
			break;
		case NSUBSHELL:
			evalsubshell(n, flags);
			do_etest = !(flags & EV_TESTED);
			break;
		case NBACKGND:
			evalsubshell(n, flags);
			break;
		case NIF: {
			evaltree(n->nif.test, EV_TESTED);
			if (evalskip)
				goto out;
			if (exitstatus == 0)
				next = n->nif.ifpart;
			else if (n->nif.elsepart)
				next = n->nif.elsepart;
			else
				exitstatus = 0;
			break;
		}
		case NWHILE:
		case NUNTIL:
			evalloop(n, flags & ~EV_EXIT);
			break;
		case NFOR:
			evalfor(n, flags & ~EV_EXIT);
			break;
		case NCASE:
			next = evalcase(n);
			break;
		case NCLIST:
			next = n->nclist.body;
			break;
		case NCLISTFALLTHRU:
			if (n->nclist.body) {
				evaltree(n->nclist.body, flags & ~EV_EXIT);
				if (evalskip)
					goto out;
			}
			next = n->nclist.next;
			break;
		case NDEFUN:
			defun(n->narg.text, n->narg.next);
			exitstatus = 0;
			break;
		case NNOT:
			evaltree(n->nnot.com, EV_TESTED);
			if (evalskip)
				goto out;
			exitstatus = !exitstatus;
			break;

		case NPIPE:
			evalpipe(n);
			do_etest = !(flags & EV_TESTED);
			break;
		case NCMD:
			evalcommand(n, flags, (struct backcmd *)NULL);
			do_etest = !(flags & EV_TESTED);
			break;
		default:
			out1fmt("Node type = %d\n", n->type);
			flushout(&output);
			break;
		}
		n = next;
		popstackmark(&smark);
		setstackmark(&smark);
	} while (n != NULL);
out:
	popstackmark(&smark);
	if (pendingsig)
		dotrap();
	if (eflag && exitstatus != 0 && do_etest)
		exitshell(exitstatus);
	if (flags & EV_EXIT)
		exraise(EXEXIT);
}