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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  show_opts (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xlog_opt ; 

__attribute__((used)) static void
usage(void)
{
  fprintf(stderr,
	  "Usage: %s [-Cfhnpv] [-a altdir] [-c cache-interval] [-g group]\n",
	  am_get_progname());
  fprintf(stderr, "\t[-i interval] [-l logfile] [-o mntopts] [-P passwdfile]\n");
  show_opts('x', xlog_opt);
#ifdef DEBUG
  show_opts('D', dbg_opt);
#endif /* DEBUG */
  fprintf(stderr, "\t[dir_name [subdir]]\n");
  exit(2);
}