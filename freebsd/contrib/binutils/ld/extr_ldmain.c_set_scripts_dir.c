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
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  BINDIR ; 
 char* SCRIPTDIR ; 
 int /*<<< orphan*/  TOOLBINDIR ; 
 scalar_t__ check_for_scripts_dir (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* make_relative_prefix (char*,int /*<<< orphan*/ ,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strrchr (char*,char) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
set_scripts_dir (void)
{
  char *end, *dir;
  size_t dirlen;
  bfd_boolean found;

  dir = make_relative_prefix (program_name, BINDIR, SCRIPTDIR);
  if (dir)
    {
      found = check_for_scripts_dir (dir);
      free (dir);
      if (found)
	return;
    }

  dir = make_relative_prefix (program_name, TOOLBINDIR, SCRIPTDIR);
  if (dir)
    {
      found = check_for_scripts_dir (dir);
      free (dir);
      if (found)
	return;
    }

  if (check_for_scripts_dir (SCRIPTDIR))
    /* We've been installed normally.  */
    return;

  /* Look for "ldscripts" in the dir where our binary is.  */
  end = strrchr (program_name, '/');
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  {
    /* We could have \foo\bar, or /foo\bar.  */
    char *bslash = strrchr (program_name, '\\');

    if (end == NULL || (bslash != NULL && bslash > end))
      end = bslash;
  }
#endif

  if (end == NULL)
    /* Don't look for ldscripts in the current directory.  There is
       too much potential for confusion.  */
    return;

  dirlen = end - program_name;
  /* Make a copy of program_name in dir.
     Leave room for later "/../lib".  */
  dir = xmalloc (dirlen + 8);
  strncpy (dir, program_name, dirlen);
  dir[dirlen] = '\0';

  if (check_for_scripts_dir (dir))
    {
      free (dir);
      return;
    }

  /* Look for "ldscripts" in <the dir where our binary is>/../lib.  */
  strcpy (dir + dirlen, "/../lib");
  check_for_scripts_dir (dir);
  free (dir);
}