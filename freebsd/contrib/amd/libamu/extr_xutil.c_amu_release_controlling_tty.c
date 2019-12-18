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

/* Variables and functions */
 scalar_t__ ENOTTY ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

void
amu_release_controlling_tty(void)
{
  int fd;

  /*
   * In daemon mode, leaving open file descriptors to terminals or pipes
   * can be a really bad idea.
   * Case in point: the redhat startup script calls us through their 'initlog'
   * program, which exits as soon as the original amd process exits. If,
   * at some point, a misbehaved library function decides to print something
   * to the screen, we get a SIGPIPE and die.
   * And guess what: NIS glibc functions will attempt to print to stderr
   * "YPBINDPROC_DOMAIN: Domain not bound" if ypbind is running but can't find
   * a ypserver.
   *
   * So we close all of our "terminal" filedescriptors, i.e. 0, 1 and 2, then
   * reopen them as /dev/null.
   *
   * XXX We should also probably set the SIGPIPE handler to SIG_IGN.
   */
  fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
    plog(XLOG_WARNING, "Could not open /dev/null for rw: %m");
  } else {
    fflush(stdin);  close(0); dup2(fd, 0);
    fflush(stdout); close(1); dup2(fd, 1);
    fflush(stderr); close(2); dup2(fd, 2);
    close(fd);
  }

#ifdef HAVE_SETSID
  /* XXX: one day maybe use vhangup(2) */
  if (setsid() < 0) {
    plog(XLOG_WARNING, "Could not release controlling tty using setsid(): %m");
  } else {
    plog(XLOG_INFO, "released controlling tty using setsid()");
    return;
  }
#endif /* HAVE_SETSID */

#ifdef TIOCNOTTY
  fd = open("/dev/tty", O_RDWR);
  if (fd < 0) {
    /* not an error if already no controlling tty */
    if (errno != ENXIO)
      plog(XLOG_WARNING, "Could not open controlling tty: %m");
  } else {
    if (ioctl(fd, TIOCNOTTY, 0) < 0 && errno != ENOTTY)
      plog(XLOG_WARNING, "Could not disassociate tty (TIOCNOTTY): %m");
    else
      plog(XLOG_INFO, "released controlling tty using ioctl(TIOCNOTTY)");
    close(fd);
  }
  return;
#else
  plog(XLOG_ERROR, "unable to release controlling tty");
#endif /* not TIOCNOTTY */
}