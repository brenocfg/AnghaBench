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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 char const* P_tmpdir ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TMPDIR_ENV ; 
 int errno ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* tmpname ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static int
temporary_file (void)
{
  char const *tmpdir = getenv (TMPDIR_ENV);
  char const *dir = tmpdir ? tmpdir : P_tmpdir;
  char *buf = xmalloc (strlen (dir) + 1 + 5 + 6 + 1);
  int fd;
  int e;
  sigset_t procmask;
  sigset_t blocked;
  sprintf (buf, "%s/sdiffXXXXXX", dir);
  sigemptyset (&blocked);
  sigaddset (&blocked, SIGINT);
  sigprocmask (SIG_BLOCK, &blocked, &procmask);
  fd = mkstemp (buf);
  e = errno;
  if (0 <= fd)
    tmpname = buf;
  sigprocmask (SIG_SETMASK, &procmask, 0);
  errno = e;
  return fd;
}