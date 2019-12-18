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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int FD_SETSIZE ; 
 int O_NOCTTY ; 
 int O_WRONLY ; 
 int STDERR_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execve (char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (scalar_t__) ; 
 int open (char*,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  set_nonblock (int) ; 
 int /*<<< orphan*/  vfork () ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_map_open(char *emap, char *key)
{
  pid_t p1, p2;
  int pdes[2], nullfd, i;
  char *argv[3];

  if (!emap)
    return 0;

  argv[0] = emap;
  argv[1] = key;
  argv[2] = NULL;

  if ((nullfd = open("/dev/null", O_WRONLY|O_NOCTTY)) < 0)
    return -1;

  if (pipe(pdes) < 0) {
    close(nullfd);
    return -1;
  }

  switch ((p1 = vfork())) {
  case -1:
    /* parent: fork error */
    close(nullfd);
    close(pdes[0]);
    close(pdes[1]);
    return -1;
  case 0:
    /* child #1 */
    p2 = vfork();
    switch (p2) {
    case -1:
      /* child #1: fork error */
      exit(errno);
    case 0:
      /* child #2: init will reap our status */
      if (pdes[1] != STDOUT_FILENO) {
	dup2(pdes[1], STDOUT_FILENO);
	close(pdes[1]);
      }

      if (nullfd != STDERR_FILENO) {
	dup2(nullfd, STDERR_FILENO);
	close(nullfd);
      }

      for (i=0; i<FD_SETSIZE; i++)
	if (i != STDOUT_FILENO  &&  i != STDERR_FILENO)
	  close(i);

      /* make the write descriptor non-blocking */
      if (!set_nonblock(STDOUT_FILENO)) {
	close(STDOUT_FILENO);
	exit(-1);
      }

      execve(emap, argv, NULL);
      exit(errno);		/* in case execve failed */
    }

    /* child #1 */
    exit(0);
  }

  /* parent */
  close(nullfd);
  close(pdes[1]);

  /* anti-zombie insurance */
  while (waitpid(p1, 0, 0) < 0)
    if (errno != EINTR)
      exit(errno);

  /* make the read descriptor non-blocking */
  if (!set_nonblock(pdes[0])) {
    close(pdes[0]);
    return -1;
  }

  return pdes[0];
}