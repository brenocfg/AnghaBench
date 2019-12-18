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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 char* savestring (char*,int) ; 
 char* skip_spaces (char*) ; 
 int strcspn (char*,char*) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char const*) ; 

char *
scan_filename_with_cleanup (char **cmd, const char *defname)
{
  char *filename;
  char *fullname;

  /* FIXME: Need to get the ``/a(ppend)'' flag from somewhere.  */

  /* File.  */
  if ((*cmd) == NULL)
    {
      if (defname == NULL)
	error ("Missing filename.");
      filename = xstrdup (defname);
      make_cleanup (xfree, filename);
    }
  else
    {
      /* FIXME: should parse a possibly quoted string.  */
      char *end;

      (*cmd) = skip_spaces (*cmd);
      end = *cmd + strcspn (*cmd, " \t");
      filename = savestring ((*cmd), end - (*cmd));
      make_cleanup (xfree, filename);
      (*cmd) = skip_spaces (end);
    }
  gdb_assert (filename != NULL);

  fullname = tilde_expand (filename);
  make_cleanup (xfree, fullname);
  
  return fullname;
}