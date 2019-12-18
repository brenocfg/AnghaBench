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
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ readlink (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 
 char* xcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfree ; 

char *
child_pid_to_exec_file (int pid)
{
  char *path;
  char *buf;

  xasprintf (&path, "/proc/%d/file", pid);
  buf = xcalloc (MAXPATHLEN, sizeof (char));
  make_cleanup (xfree, path);
  make_cleanup (xfree, buf);

  if (readlink (path, buf, MAXPATHLEN) > 0)
    return buf;

  return NULL;
}