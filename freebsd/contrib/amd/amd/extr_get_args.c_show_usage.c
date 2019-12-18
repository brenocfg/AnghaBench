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
 char* am_get_progname () ; 
 int /*<<< orphan*/  dbg_opt ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_opts (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xlog_opt ; 

__attribute__((used)) static void
show_usage(void)
{
  fprintf(stderr,
	  "Usage: %s [-nprvHS] [-a mount_point] [-c cache_time] [-d domain]\n\
\t[-k kernel_arch] [-l logfile%s\n\
\t[-t timeout.retrans] [-w wait_timeout] [-A arch] [-C cluster_name]\n\
\t[-o op_sys_ver] [-O op_sys_name]\n\
\t[-F conf_file] [-T conf_tag]", am_get_progname(),
#ifdef HAVE_SYSLOG
# ifdef LOG_DAEMON
	  "|\"syslog[:facility]\"]"
# else /* not LOG_DAEMON */
	  "|\"syslog\"]"
# endif /* not LOG_DAEMON */
#else /* not HAVE_SYSLOG */
	  "]"
#endif /* not HAVE_SYSLOG */
	  );

#ifdef HAVE_MAP_NIS
  fputs(" [-y nis-domain]\n", stderr);
#else /* not HAVE_MAP_NIS */
  fputc('\n', stderr);
#endif /* HAVE_MAP_NIS */

  show_opts('x', xlog_opt);
#ifdef DEBUG
  show_opts('D', dbg_opt);
#endif /* DEBUG */
  fprintf(stderr, "\t[directory mapname [-map_options]] ...\n");
}