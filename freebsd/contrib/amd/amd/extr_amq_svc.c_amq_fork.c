#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int sigset_t ;
typedef  int pid_t ;
typedef  scalar_t__ opaque_t ;
struct TYPE_3__ {int* am_fd; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int background () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dlog (char*) ; 
 scalar_t__ errno ; 
 TYPE_1__* find_ap (char*) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  sigaddset (int*,int /*<<< orphan*/ ) ; 
 int sigblock (int) ; 
 int /*<<< orphan*/  sigemptyset (int*) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 

__attribute__((used)) static int
amq_fork(opaque_t argp)
{
#ifdef HAVE_SIGACTION
  sigset_t new, mask;
#else /* not HAVE_SIGACTION */
  int mask;
#endif /* not HAVE_SIGACTION */
  am_node *mp;
  pid_t pid;

  mp = find_ap(*(char **) argp);
  if (mp == NULL) {
    errno = 0;
    return -1;
  }

  if (pipe(mp->am_fd) == -1) {
    mp->am_fd[0] = -1;
    mp->am_fd[1] = -1;
    return -1;
  }

#ifdef HAVE_SIGACTION
  sigemptyset(&new);		/* initialize signal set we wish to block */
  sigaddset(&new, SIGHUP);
  sigaddset(&new, SIGINT);
  sigaddset(&new, SIGQUIT);
  sigaddset(&new, SIGCHLD);
  sigprocmask(SIG_BLOCK, &new, &mask);
#else /* not HAVE_SIGACTION */
  mask =
      sigmask(SIGHUP) |
      sigmask(SIGINT) |
      sigmask(SIGQUIT) |
      sigmask(SIGCHLD);
  mask = sigblock(mask);
#endif /* not HAVE_SIGACTION */

  switch ((pid = background())) {
  case -1:	/* error */
    dlog("amq_fork failed");
    return -1;

  case 0:	/* child */
    close(mp->am_fd[1]);	/* close output end of pipe */
    mp->am_fd[1] = -1;
    return 0;

  default:	/* parent */
    close(mp->am_fd[0]);	/* close input end of pipe */
    mp->am_fd[0] = -1;

#ifdef HAVE_SIGACTION
    sigprocmask(SIG_SETMASK, &mask, NULL);
#else /* not HAVE_SIGACTION */
    sigsetmask(mask);
#endif /* not HAVE_SIGACTION */
    return pid;
  }
}