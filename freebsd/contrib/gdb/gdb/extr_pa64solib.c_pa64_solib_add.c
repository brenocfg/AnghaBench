#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct load_module_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dll_desc ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {int dld_flags; int /*<<< orphan*/  load_map; int /*<<< orphan*/  have_read_dld_descriptor; } ;
struct TYPE_3__ {int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int DT_HP_DEBUG_PRIVATE ; 
 int /*<<< orphan*/  add_to_solist (int,char*,int,struct load_module_desc*,int /*<<< orphan*/ ,struct target_ops*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ dld_cache ; 
 scalar_t__ dlgetmodinfo (int,struct load_module_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dlgetname (struct load_module_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  pa64_target_read_memory ; 
 char* re_comp (char*) ; 
 int /*<<< orphan*/  read_dld_descriptor (struct target_ops*,int) ; 
 TYPE_1__* symfile_objfile ; 
 int /*<<< orphan*/  warning (char*) ; 

void
pa64_solib_add (char *arg_string, int from_tty, struct target_ops *target, int readsyms)
{
  struct minimal_symbol *msymbol;
  CORE_ADDR addr;
  asection *shlib_info;
  int status;
  unsigned int dld_flags;
  char buf[4], *re_err;
  int threshold_warning_given = 0;
  int dll_index;
  struct load_module_desc dll_desc;
  char *dll_path;

  /* First validate our arguments.  */
  if ((re_err = re_comp (arg_string ? arg_string : ".")) != NULL)
    {
      error ("Invalid regexp: %s", re_err);
    }

  /* If we're debugging a core file, or have attached to a running
     process, then pa64_solib_create_inferior_hook will not have been
     called.

     We need to first determine if we're dealing with a dynamically
     linked executable.  If not, then return without an error or warning.

     We also need to examine __dld_flags to determine if the shared library
     list is valid and to determine if the libraries have been privately
     mapped.  */
  if (symfile_objfile == NULL)
    return;

  /* First see if the objfile was dynamically linked.  */
  shlib_info = bfd_get_section_by_name (symfile_objfile->obfd, ".dynamic");
  if (!shlib_info)
    return;

  /* It's got a .dynamic section, make sure it's not empty.  */
  if (bfd_section_size (symfile_objfile->obfd, shlib_info) == 0)
    return;

  /* Read in the load map pointer if we have not done so already.  */
  if (! dld_cache.have_read_dld_descriptor)
    if (! read_dld_descriptor (target, readsyms))
      return;

  /* If the libraries were not mapped private, warn the user.  */
  if ((dld_cache.dld_flags & DT_HP_DEBUG_PRIVATE) == 0)
    warning ("The shared libraries were not privately mapped; setting a\nbreakpoint in a shared library will not work until you rerun the program.\n");

  /* For each shaerd library, add it to the shared library list.  */
  for (dll_index = 1; ; dll_index++)
    {
      /* Read in the load module descriptor.  */
      if (dlgetmodinfo (dll_index, &dll_desc, sizeof (dll_desc),
			pa64_target_read_memory, 0, dld_cache.load_map)
	  == 0)
	return;

      /* Get the name of the shared library.  */
      dll_path = (char *)dlgetname (&dll_desc, sizeof (dll_desc),
			    pa64_target_read_memory,
			    0, dld_cache.load_map);

      if (!dll_path)
	error ("pa64_solib_add, unable to read shared library path.");

      add_to_solist (from_tty, dll_path, readsyms, &dll_desc, 0, target);
    }
}