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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int mode_t ;
struct TYPE_2__ {int flags; char* pid_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CFM_PRINT_PID ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ STREQ (char*,char*) ; 
 scalar_t__ am_mypid ; 
 int /*<<< orphan*/  amu_release_controlling_tty () ; 
 int background () ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int foreground ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getppid () ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parent_exit ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int umask (int) ; 

__attribute__((used)) static int
daemon_mode(void)
{
  int bgpid;

#ifdef HAVE_SIGACTION
  struct sigaction sa, osa;

  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = parent_exit;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGQUIT);
  sigaction(SIGQUIT, &sa, &osa);
#else /* not HAVE_SIGACTION */
  signal(SIGQUIT, parent_exit);
#endif /* not HAVE_SIGACTION */

  bgpid = background();

  if (bgpid != 0) {
    /*
     * Now wait for the automount points to
     * complete.
     */
    for (;;)
      pause();
    /* should never reach here */
  }
#ifdef HAVE_SIGACTION
  sigaction(SIGQUIT, &osa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGQUIT, SIG_DFL);
#endif /* not HAVE_SIGACTION */

  /*
   * Record our pid to make it easier to kill the correct amd.
   */
  if (gopt.flags & CFM_PRINT_PID) {
    if (STREQ(gopt.pid_file, "/dev/stdout")) {
      printf("%ld\n", (long) am_mypid);
      /* flush stdout, just in case */
      fflush(stdout);
    } else {
      FILE *f;
      mode_t prev_umask = umask(0022); /* set secure temporary umask */

      f = fopen(gopt.pid_file, "w");
      if (f) {
	fprintf(f, "%ld\n", (long) am_mypid);
	(void) fclose(f);
      } else {
	fprintf(stderr, "cannot open %s (errno=%d)\n", gopt.pid_file, errno);
      }
      umask(prev_umask);	/* restore umask */
    }
  }

  /*
   * Pretend we are in the foreground again
   */
  foreground = 1;

  /*
   * Dissociate from the controlling terminal
   */
  amu_release_controlling_tty();

  return getppid();
}