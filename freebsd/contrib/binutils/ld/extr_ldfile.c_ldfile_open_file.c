#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; struct TYPE_8__* next; } ;
typedef  TYPE_1__ search_arch_type ;
struct TYPE_9__ {int /*<<< orphan*/  local_sym_name; scalar_t__ sysrooted; void* search_dirs_flag; int /*<<< orphan*/  filename; int /*<<< orphan*/ * the_bfd; } ;
typedef  TYPE_2__ lang_input_statement_type ;
typedef  void* bfd_boolean ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ IS_ABSOLUTE_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ld_sysroot ; 
 void* ldemul_find_potential_libraries (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* ldfile_open_file_search (int /*<<< orphan*/ ,TYPE_2__*,char*,char*) ; 
 scalar_t__ ldfile_try_open_bfd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* search_arch_head ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ldfile_open_file (lang_input_statement_type *entry)
{
  if (entry->the_bfd != NULL)
    return;

  if (! entry->search_dirs_flag)
    {
      if (ldfile_try_open_bfd (entry->filename, entry))
	return;
      if (strcmp (entry->filename, entry->local_sym_name) != 0)
	einfo (_("%F%P: %s (%s): No such file: %E\n"),
	       entry->filename, entry->local_sym_name);
      else
	einfo (_("%F%P: %s: No such file: %E\n"), entry->local_sym_name);
    }
  else
    {
      search_arch_type *arch;
      bfd_boolean found = FALSE;

      /* Try to open <filename><suffix> or lib<filename><suffix>.a */
      for (arch = search_arch_head; arch != NULL; arch = arch->next)
	{
	  found = ldfile_open_file_search (arch->name, entry, "lib", ".a");
	  if (found)
	    break;
#ifdef VMS
	  found = ldfile_open_file_search (arch->name, entry, ":lib", ".a");
	  if (found)
	    break;
#endif
	  found = ldemul_find_potential_libraries (arch->name, entry);
	  if (found)
	    break;
	}

      /* If we have found the file, we don't need to search directories
	 again.  */
      if (found)
	entry->search_dirs_flag = FALSE;
      else if (entry->sysrooted
	       && ld_sysroot
	       && IS_ABSOLUTE_PATH (entry->local_sym_name))
	einfo (_("%F%P: cannot find %s inside %s\n"),
	       entry->local_sym_name, ld_sysroot);
      else
	einfo (_("%F%P: cannot find %s\n"), entry->local_sym_name);
    }
}