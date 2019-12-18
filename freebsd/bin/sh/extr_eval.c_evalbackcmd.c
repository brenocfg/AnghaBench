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
typedef  union node {int dummy; } node ;
struct stackmark {int dummy; } ;
struct localvar {int dummy; } ;
struct job {int dummy; } ;
struct jmploc {int /*<<< orphan*/  loc; } ;
struct backcmd {int fd; struct job* jp; scalar_t__ nleft; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {unsigned char reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_BACKCMD ; 
 int /*<<< orphan*/  EV_EXIT ; 
 scalar_t__ EXERROR ; 
 int /*<<< orphan*/  FORCEINTON ; 
 int /*<<< orphan*/  FORK_NOJOB ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evalcommand (union node*,int /*<<< orphan*/ ,struct backcmd*) ; 
 int /*<<< orphan*/  evaltree (union node*,int /*<<< orphan*/ ) ; 
 scalar_t__ exception ; 
 scalar_t__ exitstatus ; 
 int /*<<< orphan*/  forcelocal ; 
 scalar_t__ forkshell (struct job*,union node*,int /*<<< orphan*/ ) ; 
 struct jmploc* handler ; 
 scalar_t__ is_valid_fast_cmdsubst (union node*) ; 
 struct localvar* localvars ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 struct job* makejob (union node*,int) ; 
 scalar_t__ oexitstatus ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  poplocalvars () ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 
 TYPE_1__ shellparam ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
evalbackcmd(union node *n, struct backcmd *result)
{
	int pip[2];
	struct job *jp;
	struct stackmark smark;
	struct jmploc jmploc;
	struct jmploc *savehandler;
	struct localvar *savelocalvars;
	unsigned char saveoptreset;

	result->fd = -1;
	result->buf = NULL;
	result->nleft = 0;
	result->jp = NULL;
	if (n == NULL) {
		exitstatus = 0;
		return;
	}
	setstackmark(&smark);
	exitstatus = oexitstatus;
	if (is_valid_fast_cmdsubst(n)) {
		savelocalvars = localvars;
		localvars = NULL;
		saveoptreset = shellparam.reset;
		forcelocal++;
		savehandler = handler;
		if (setjmp(jmploc.loc)) {
			if (exception == EXERROR)
				/* nothing */;
			else if (exception != 0) {
				handler = savehandler;
				forcelocal--;
				poplocalvars();
				localvars = savelocalvars;
				shellparam.reset = saveoptreset;
				longjmp(handler->loc, 1);
			}
		} else {
			handler = &jmploc;
			evalcommand(n, EV_BACKCMD, result);
		}
		handler = savehandler;
		forcelocal--;
		poplocalvars();
		localvars = savelocalvars;
		shellparam.reset = saveoptreset;
	} else {
		if (pipe(pip) < 0)
			error("Pipe call failed: %s", strerror(errno));
		jp = makejob(n, 1);
		if (forkshell(jp, n, FORK_NOJOB) == 0) {
			FORCEINTON;
			close(pip[0]);
			if (pip[1] != 1) {
				dup2(pip[1], 1);
				close(pip[1]);
			}
			evaltree(n, EV_EXIT);
		}
		close(pip[1]);
		result->fd = pip[0];
		result->jp = jp;
	}
	popstackmark(&smark);
	TRACE(("evalbackcmd done: fd=%d buf=%p nleft=%d jp=%p\n",
		result->fd, result->buf, result->nleft, result->jp));
}