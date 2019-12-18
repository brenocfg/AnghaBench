#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_5__ {int have_read_dld_descriptor; int /*<<< orphan*/  dld_desc; int /*<<< orphan*/  load_map; int /*<<< orphan*/  load_map_addr; int /*<<< orphan*/  is_valid; } ;
struct TYPE_4__ {int /*<<< orphan*/  obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_solist (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct target_ops*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ dld_cache ; 
 scalar_t__ dlgetmodinfo (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dlgetname (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  pa64_target_read_memory ; 
 int /*<<< orphan*/  read_dynamic_info (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* symfile_objfile ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
read_dld_descriptor (struct target_ops *target, int readsyms)
{
  char *dll_path;
  asection *dyninfo_sect;

  /* If necessary call read_dynamic_info to extract the contents of the
     .dynamic section from the shared library.  */
  if (!dld_cache.is_valid) 
    {
      if (symfile_objfile == NULL)
	error ("No object file symbols.");

      dyninfo_sect = bfd_get_section_by_name (symfile_objfile->obfd, 
					      ".dynamic");
      if (!dyninfo_sect) 
	{
	  return 0;
	}

      if (!read_dynamic_info (dyninfo_sect, &dld_cache))
	error ("Unable to read in .dynamic section information.");
    }

  /* Read the load map pointer.  */
  if (target_read_memory (dld_cache.load_map_addr,
			  (char*) &dld_cache.load_map,
			  sizeof(dld_cache.load_map))
      != 0)
    {
      error ("Error while reading in load map pointer.");
    }

  /* Read in the dld load module descriptor */
  if (dlgetmodinfo (-1, 
		    &dld_cache.dld_desc,
		    sizeof(dld_cache.dld_desc), 
		    pa64_target_read_memory, 
		    0, 
		    dld_cache.load_map)
      == 0)
    {
      error ("Error trying to get information about dynamic linker.");
    }

  /* Indicate that we have loaded the dld descriptor.  */
  dld_cache.have_read_dld_descriptor = 1;

  /* Add dld.sl to the list of known shared libraries so that we can
     do unwind, etc. 

     ?!? This may not be correct.  Consider of dld.sl contains symbols
     which are also referenced/defined by the user program or some user
     shared library.  We need to make absolutely sure that we do not
     pollute the namespace from GDB's point of view.  */
  dll_path = dlgetname (&dld_cache.dld_desc, 
			sizeof(dld_cache.dld_desc), 
			pa64_target_read_memory, 
			0, 
			dld_cache.load_map);
  add_to_solist(0, dll_path, readsyms, &dld_cache.dld_desc, 0, target);
  
  return 1;
}