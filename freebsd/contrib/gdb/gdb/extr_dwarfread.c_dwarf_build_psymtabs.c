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
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct objfile {int /*<<< orphan*/  section_offsets; TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; int /*<<< orphan*/ * obfd; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  base_section_offsets ; 
 int /*<<< orphan*/  baseaddr ; 
 unsigned int bfd_bread (scalar_t__,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct objfile* current_objfile ; 
 scalar_t__ dbbase ; 
 scalar_t__ dbroff ; 
 unsigned int dbsize ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_psymbol_list (struct objfile*,int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (scalar_t__),scalar_t__) ; 
 int /*<<< orphan*/  scan_compilation_units (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 
 scalar_t__ xmalloc (unsigned int) ; 

void
dwarf_build_psymtabs (struct objfile *objfile, int mainline, file_ptr dbfoff,
		      unsigned int dbfsize, file_ptr lnoffset,
		      unsigned int lnsize)
{
  bfd *abfd = objfile->obfd;
  struct cleanup *back_to;

  current_objfile = objfile;
  dbsize = dbfsize;
  dbbase = xmalloc (dbsize);
  dbroff = 0;
  if ((bfd_seek (abfd, dbfoff, SEEK_SET) != 0) ||
      (bfd_bread (dbbase, dbsize, abfd) != dbsize))
    {
      xfree (dbbase);
      error ("can't read DWARF data from '%s'", bfd_get_filename (abfd));
    }
  back_to = make_cleanup (xfree, dbbase);

  /* If we are reinitializing, or if we have never loaded syms yet, init.
     Since we have no idea how many DIES we are looking at, we just guess
     some arbitrary value. */

  if (mainline
      || (objfile->global_psymbols.size == 0
	  && objfile->static_psymbols.size == 0))
    {
      init_psymbol_list (objfile, 1024);
    }

  /* Save the relocation factor where everybody can see it.  */

  base_section_offsets = objfile->section_offsets;
  baseaddr = ANOFFSET (objfile->section_offsets, 0);

  /* Follow the compilation unit sibling chain, building a partial symbol
     table entry for each one.  Save enough information about each compilation
     unit to locate the full DWARF information later. */

  scan_compilation_units (dbbase, dbbase + dbsize, dbfoff, lnoffset, objfile);

  do_cleanups (back_to);
  current_objfile = NULL;
}