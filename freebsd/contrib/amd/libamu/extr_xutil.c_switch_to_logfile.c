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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LOG_NOWAIT ; 
 int LOG_PID ; 
 scalar_t__ NSTREQ (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  __IGNORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am_get_progname () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  get_syslog_facility (char*) ; 
 int /*<<< orphan*/ * logfp ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int syslogging ; 
 int /*<<< orphan*/  truncate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int) ; 

int
switch_to_logfile(char *logfile, int old_umask, int truncate_log)
{
  FILE *new_logfp = stderr;

  if (logfile) {
#ifdef HAVE_SYSLOG
    syslogging = 0;
#endif /* HAVE_SYSLOG */

    if (STREQ(logfile, "/dev/stderr"))
      new_logfp = stderr;
    else if (NSTREQ(logfile, "syslog", strlen("syslog"))) {

#ifdef HAVE_SYSLOG
      syslogging = 1;
      new_logfp = stderr;
      openlog(am_get_progname(),
	      LOG_PID
# ifdef LOG_NOWAIT
	      | LOG_NOWAIT
# endif /* LOG_NOWAIT */
# ifdef LOG_DAEMON
	      , get_syslog_facility(logfile)
# endif /* LOG_DAEMON */
	      );
#else /* not HAVE_SYSLOG */
      plog(XLOG_WARNING, "syslog option not supported, logging unchanged");
#endif /* not HAVE_SYSLOG */

    } else {			/* regular log file */
      (void) umask(old_umask);
      if (truncate_log)
	__IGNORE(truncate(logfile, 0));
      new_logfp = fopen(logfile, "a");
      umask(0);
    }
  }

  /*
   * If we couldn't open a new file, then continue using the old.
   */
  if (!new_logfp && logfile) {
    plog(XLOG_USER, "%s: Can't open logfile: %m", logfile);
    return 1;
  }

  /*
   * Close the previous file
   */
  if (logfp && logfp != stderr)
    (void) fclose(logfp);
  logfp = new_logfp;

  if (logfile)
    plog(XLOG_INFO, "switched to logfile \"%s\"", logfile);
  else
    plog(XLOG_INFO, "no logfile defined; using stderr");

  return 0;
}