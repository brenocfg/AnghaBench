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
struct pid {int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int errno ; 
 int /*<<< orphan*/  execve (char const*,char* const*,char* const*) ; 
 int /*<<< orphan*/  pdes_child (int*,char const*) ; 
 int /*<<< orphan*/  pdes_error (int*,struct pid*) ; 
 struct pid* pdes_get (int*,char const**) ; 
 int /*<<< orphan*/  pdes_parent (int*,struct pid*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pidlist_lock ; 
 int /*<<< orphan*/  rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfork () ; 

FILE *
popenve(const char *cmd, char *const *argv, char *const *envp, const char *type)
{
	struct pid *cur;
	int pdes[2], serrno;
	pid_t pid;

	if ((cur = pdes_get(pdes, &type)) == NULL)
		return NULL;

#ifdef _REENTRANT
	(void)rwlock_rdlock(&pidlist_lock);
#endif
	switch (pid = vfork()) {
	case -1:			/* Error. */
		serrno = errno;
#ifdef _REENTRANT
		(void)rwlock_unlock(&pidlist_lock);
#endif
		pdes_error(pdes, cur);
		errno = serrno;
		return NULL;
		/* NOTREACHED */
	case 0:				/* Child. */
		pdes_child(pdes, type);
		execve(cmd, argv, envp);
		_exit(127);
		/* NOTREACHED */
	}

	pdes_parent(pdes, cur, pid, type);

#ifdef _REENTRANT
	(void)rwlock_unlock(&pidlist_lock);
#endif

	return cur->fp;
}