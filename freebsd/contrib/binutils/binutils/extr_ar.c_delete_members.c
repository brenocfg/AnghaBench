#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* bfd_boolean ;
struct TYPE_5__ {struct TYPE_5__* archive_next; int /*<<< orphan*/  filename; void* has_armap; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ FILENAME_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 char* _ (char*) ; 
 int counted_name_counter ; 
 scalar_t__ counted_name_mode ; 
 int /*<<< orphan*/  normalize (char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * output_filename ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_archive (TYPE_1__*) ; 
 int write_armap ; 

__attribute__((used)) static void
delete_members (bfd *arch, char **files_to_delete)
{
  bfd **current_ptr_ptr;
  bfd_boolean found;
  bfd_boolean something_changed = FALSE;
  int match_count;

  for (; *files_to_delete != NULL; ++files_to_delete)
    {
      /* In a.out systems, the armap is optional.  It's also called
	 __.SYMDEF.  So if the user asked to delete it, we should remember
	 that fact. This isn't quite right for COFF systems (where
	 __.SYMDEF might be regular member), but it's very unlikely
	 to be a problem.  FIXME */

      if (!strcmp (*files_to_delete, "__.SYMDEF"))
	{
	  arch->has_armap = FALSE;
	  write_armap = -1;
	  continue;
	}

      found = FALSE;
      match_count = 0;
      current_ptr_ptr = &(arch->archive_next);
      while (*current_ptr_ptr)
	{
	  if (FILENAME_CMP (normalize (*files_to_delete, arch),
			    (*current_ptr_ptr)->filename) == 0)
	    {
	      ++match_count;
	      if (counted_name_mode
		  && match_count != counted_name_counter)
		{
		  /* Counting, and didn't match on count; go on to the
                     next one.  */
		}
	      else
		{
		  found = TRUE;
		  something_changed = TRUE;
		  if (verbose)
		    printf ("d - %s\n",
			    *files_to_delete);
		  *current_ptr_ptr = ((*current_ptr_ptr)->archive_next);
		  goto next_file;
		}
	    }

	  current_ptr_ptr = &((*current_ptr_ptr)->archive_next);
	}

      if (verbose && !found)
	{
	  /* xgettext:c-format */
	  printf (_("No member named `%s'\n"), *files_to_delete);
	}
    next_file:
      ;
    }

  if (something_changed)
    write_archive (arch);
  else
    output_filename = NULL;
}