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
struct TYPE_6__ {char* expdoc; TYPE_2__* doc; } ;
union node {scalar_t__ type; TYPE_3__ nhere; } ;
struct job {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {char* text; } ;
struct TYPE_5__ {TYPE_1__ narg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORK_NOJOB ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ NXHERE ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ forkshell (struct job*,union node*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ write (int,char const*,size_t) ; 
 int /*<<< orphan*/  xwrite (int,char const*,scalar_t__) ; 

__attribute__((used)) static int
openhere(union node *redir)
{
	const char *p;
	int pip[2];
	size_t len = 0;
	int flags;
	ssize_t written = 0;

	if (pipe(pip) < 0)
		error("Pipe call failed: %s", strerror(errno));

	if (redir->type == NXHERE)
		p = redir->nhere.expdoc;
	else
		p = redir->nhere.doc->narg.text;
	len = strlen(p);
	if (len == 0)
		goto out;
	flags = fcntl(pip[1], F_GETFL, 0);
	if (flags != -1 && fcntl(pip[1], F_SETFL, flags | O_NONBLOCK) != -1) {
		written = write(pip[1], p, len);
		if (written < 0)
			written = 0;
		if ((size_t)written == len)
			goto out;
		fcntl(pip[1], F_SETFL, flags);
	}

	if (forkshell((struct job *)NULL, (union node *)NULL, FORK_NOJOB) == 0) {
		close(pip[0]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGPIPE, SIG_DFL);
		xwrite(pip[1], p + written, len - written);
		_exit(0);
	}
out:
	close(pip[1]);
	return pip[0];
}