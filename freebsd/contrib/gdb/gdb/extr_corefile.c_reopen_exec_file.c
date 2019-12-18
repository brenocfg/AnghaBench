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
struct stat {long st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_get_mtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reopen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * exec_bfd ; 
 int /*<<< orphan*/  exec_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  target_shortname ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

void
reopen_exec_file (void)
{
#if 0				/* FIXME */
  if (exec_bfd)
    bfd_reopen (exec_bfd);
#else
  char *filename;
  int res;
  struct stat st;
  long mtime;

  /* Don't do anything if the current target isn't exec. */
  if (exec_bfd == NULL || strcmp (target_shortname, "exec") != 0)
    return;

  /* If the timestamp of the exec file has changed, reopen it. */
  filename = xstrdup (bfd_get_filename (exec_bfd));
  make_cleanup (xfree, filename);
  mtime = bfd_get_mtime (exec_bfd);
  res = stat (filename, &st);

  if (mtime && mtime != st.st_mtime)
    {
      exec_open (filename, 0);
    }
#endif
}