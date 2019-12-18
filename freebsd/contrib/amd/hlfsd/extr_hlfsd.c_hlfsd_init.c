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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  (* sa_handler ) (int /*<<< orphan*/ ) ;} ;
struct itimerval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DAEMON ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int am_set_mypid () ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amu_release_controlling_tty () ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fork () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  hlfsd_init_filehandles () ; 
 int /*<<< orphan*/  interlock (int /*<<< orphan*/ ) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int masterpid ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  plt_init () ; 
 int /*<<< orphan*/  plt_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reloadinterval ; 
 int serverpid ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct itimerval*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  startup ; 
 int /*<<< orphan*/  svc_run () ; 

__attribute__((used)) static void
hlfsd_init(void)
{
  int child = 0;
#ifdef HAVE_SIGACTION
  struct sigaction sa;
#endif /* HAVE_SIGACTION */

  /*
   * Initialize file handles.
   */
  plog(XLOG_INFO, "initializing hlfsd file handles");
  hlfsd_init_filehandles();

  /*
   * If -D daemon then we must fork.
   */
  if (amuDebug(D_DAEMON))
    child = fork();

  if (child < 0)
    fatal("fork: %m");

  if (child != 0) {		/* parent process - save child pid */
    masterpid = child;
    am_set_mypid();		/* for logging routines */
    return;
  }

  /*
   * CHILD CODE:
   * initialize server
   */

  plog(XLOG_INFO, "initializing home directory database");
  plt_init();			/* initialize database */
  plog(XLOG_INFO, "home directory database initialized");

  masterpid = serverpid = am_set_mypid(); /* for logging routines */

  /*
   * SIGALRM/SIGHUP: reload password database if timer expired
   * or user sent HUP signal.
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = reload;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGALRM);
  sigaddset(&(sa.sa_mask), SIGHUP);
  sigaction(SIGALRM, &sa, NULL);
  sigaction(SIGHUP, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGALRM, reload);
  signal(SIGHUP, reload);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGTERM: cleanup and exit.
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = cleanup;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGTERM);
  sigaction(SIGTERM, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGTERM, cleanup);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGCHLD: interlock synchronization and testing
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = interlock;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGCHLD);
  sigaction(SIGCHLD, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGCHLD, interlock);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGUSR1: dump internal hlfsd maps/cache to file
   */
#ifdef HAVE_SIGACTION
# if defined(DEBUG) || defined(DEBUG_PRINT)
  sa.sa_handler = plt_print;
# else /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  sa.sa_handler = SIG_IGN;
# endif /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGUSR1);
  sigaction(SIGUSR1, &sa, NULL);
#else /* not HAVE_SIGACTION */
# if defined(DEBUG) || defined(DEBUG_PRINT)
  signal(SIGUSR1, plt_print);
# else /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  signal(SIGUSR1, SIG_IGN);
# endif /* not defined(DEBUG) || defined(DEBUG_PRINT) */
#endif /* not HAVE_SIGACTION */

  if (setitimer(ITIMER_REAL, &reloadinterval, (struct itimerval *) NULL) < 0)
    fatal("setitimer: %m");

  clocktime(&startup);

  /*
   * If -D daemon, then start serving here in the child,
   * and the parent will exit.  But if -D nodaemon, then
   * skip this code and make sure svc_run is entered elsewhere.
   */
  if (amuDebug(D_DAEMON)) {
    /*
     * Dissociate from the controlling terminal
     */
    amu_release_controlling_tty();

    /*
     * signal parent we are ready. parent should
     * mount(2) and die.
     */
    if (kill(getppid(), SIGUSR2) < 0)
      fatal("kill: %m");
    plog(XLOG_INFO, "starting svc_run");
    svc_run();
    cleanup(0);		/* should never happen, just in case */
  }

}