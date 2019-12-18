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
struct objfile {struct obj_section* sections_end; struct obj_section* sections; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  obfd; } ;
struct obj_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_objfile_sections ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ obstack_finish (int /*<<< orphan*/ *) ; 

int
build_objfile_section_table (struct objfile *objfile)
{
  /* objfile->sections can be already set when reading a mapped symbol
     file.  I believe that we do need to rebuild the section table in
     this case (we rebuild other things derived from the bfd), but we
     can't free the old one (it's in the objfile_obstack).  So we just
     waste some memory.  */

  objfile->sections_end = 0;
  bfd_map_over_sections (objfile->obfd, add_to_objfile_sections, (char *) objfile);
  objfile->sections = (struct obj_section *)
    obstack_finish (&objfile->objfile_obstack);
  objfile->sections_end = objfile->sections + (unsigned long) objfile->sections_end;
  return (0);
}