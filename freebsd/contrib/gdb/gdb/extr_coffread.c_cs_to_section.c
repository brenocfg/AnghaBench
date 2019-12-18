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
struct objfile {int /*<<< orphan*/  obfd; } ;
struct find_targ_sec_arg {TYPE_1__** resultp; int /*<<< orphan*/  targ_index; } ;
struct coff_symbol {int /*<<< orphan*/  c_secnum; } ;
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SECT_OFF_DATA (struct objfile*) ; 
 int SECT_OFF_TEXT (struct objfile*) ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  abfd ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_targ_sec_arg*) ; 
 int /*<<< orphan*/  find_targ_sec ; 

__attribute__((used)) static int
cs_to_section (struct coff_symbol *cs, struct objfile *objfile)
{
  asection *sect = NULL;
  struct find_targ_sec_arg args;
  int off = SECT_OFF_TEXT (objfile);

  args.targ_index = cs->c_secnum;
  args.resultp = &sect;
  bfd_map_over_sections (objfile->obfd, find_targ_sec, &args);
  if (sect != NULL)
    {
      /* This is the section.  Figure out what SECT_OFF_* code it is.  */
      if (bfd_get_section_flags (abfd, sect) & SEC_CODE)
	off = SECT_OFF_TEXT (objfile);
      else if (bfd_get_section_flags (abfd, sect) & SEC_LOAD)
	off = SECT_OFF_DATA (objfile);
      else
	/* Just return the bfd section index. */
	off = sect->index;
    }
  return off;
}