#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* symbol; } ;
typedef  TYPE_1__ hash_table_entry ;

/* Variables and functions */
 scalar_t__ IS_SAME_PATH (int /*<<< orphan*/ ,char const*) ; 
 char* alloca (int) ; 
 char const* cplus_suffix ; 
 int errno ; 
 int /*<<< orphan*/  errors ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname ; 
 int rename (char const*,char* const) ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,char* const) ; 
 int /*<<< orphan*/  strcpy (char* const,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  syscalls_absolute_filename ; 
 int /*<<< orphan*/  xstrerror (int) ; 

__attribute__((used)) static void
rename_c_file (const hash_table_entry *hp)
{
  const char *filename = hp->symbol;
  int last_char_index = strlen (filename) - 1;
  char *const new_filename = alloca (strlen (filename)
				     + strlen (cplus_suffix) + 1);

  /* Note that we don't care here if the given file was converted or not.  It
     is possible that the given file was *not* converted, simply because there
     was nothing in it which actually required conversion.  Even in this case,
     we want to do the renaming.  Note that we only rename files with the .c
     suffix (except for the syscalls file, which is left alone).  */

  if (filename[last_char_index] != 'c' || filename[last_char_index-1] != '.'
      || IS_SAME_PATH (syscalls_absolute_filename, filename))
    return;

  strcpy (new_filename, filename);
  strcpy (&new_filename[last_char_index], cplus_suffix);

  if (rename (filename, new_filename) == -1)
    {
      int errno_val = errno;
      notice ("%s: warning: can't rename file '%s' to '%s': %s\n",
	      pname, shortpath (NULL, filename),
	      shortpath (NULL, new_filename), xstrerror (errno_val));
      errors++;
      return;
    }
}