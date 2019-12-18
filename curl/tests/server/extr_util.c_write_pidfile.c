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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,long) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int write_pidfile(const char *filename)
{
  FILE *pidfile;
  long pid;

  pid = (long)getpid();
  pidfile = fopen(filename, "wb");
  if(!pidfile) {
    logmsg("Couldn't write pid file: %s %s", filename, strerror(errno));
    return 0; /* fail */
  }
  fprintf(pidfile, "%ld\n", pid);
  fclose(pidfile);
  logmsg("Wrote pid %ld to %s", pid, filename);
  return 1; /* success */
}