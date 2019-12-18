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
struct pid {int fd; int /*<<< orphan*/  fp; struct pid* next; } ;

/* Variables and functions */
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 struct pid* pidlist ; 

__attribute__((used)) static void
pdes_child(int *pdes, const char *type)
{
	struct pid *old;

	/* POSIX.2 B.3.2.2 "popen() shall ensure that any streams
	   from previous popen() calls that remain open in the 
	   parent process are closed in the new child process. */
	for (old = pidlist; old; old = old->next)
#ifdef _REENTRANT
		(void)close(old->fd); /* don't allow a flush */
#else
		(void)close(fileno(old->fp)); /* don't allow a flush */
#endif

	if (type[0] == 'r') {
		(void)close(pdes[0]);
		if (pdes[1] != STDOUT_FILENO) {
			(void)dup2(pdes[1], STDOUT_FILENO);
			(void)close(pdes[1]);
		}
		if (type[1] == '+')
			(void)dup2(STDOUT_FILENO, STDIN_FILENO);
	} else {
		(void)close(pdes[1]);
		if (pdes[0] != STDIN_FILENO) {
			(void)dup2(pdes[0], STDIN_FILENO);
			(void)close(pdes[0]);
		}
	}
}