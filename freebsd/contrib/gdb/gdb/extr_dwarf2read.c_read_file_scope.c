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
struct type {int dummy; } ;
struct TYPE_3__ {scalar_t__ entry_point; scalar_t__ deprecated_entry_file_highpc; scalar_t__ deprecated_entry_file_lowpc; } ;
struct objfile {TYPE_1__ ei; int /*<<< orphan*/  section_offsets; int /*<<< orphan*/ * obfd; } ;
struct line_header {int dummy; } ;
struct comp_unit_head {int dummy; } ;
struct dwarf2_cu {int /*<<< orphan*/  ftypes; struct comp_unit_head header; struct objfile* objfile; } ;
struct die_info {scalar_t__ tag; struct die_info* child; } ;
struct cleanup {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  make_cleanup_ftype ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/ * at_producer; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_AT_comp_dir ; 
 int /*<<< orphan*/  DW_AT_language ; 
 int /*<<< orphan*/  DW_AT_macro_info ; 
 int /*<<< orphan*/  DW_AT_name ; 
 int /*<<< orphan*/  DW_AT_stmt_list ; 
 char* DW_STRING (struct attribute*) ; 
 unsigned int DW_UNSND (struct attribute*) ; 
 int FT_NUM_MEMBERS ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 TYPE_2__* dip ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct attribute* dwarf2_attr (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 struct line_header* dwarf_decode_line_header (unsigned int,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf_decode_lines (struct line_header*,char*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf_decode_macros (struct line_header*,unsigned int,char*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 scalar_t__ free_line_header ; 
 int /*<<< orphan*/  get_scope_pc_bounds (struct die_info*,scalar_t__*,scalar_t__*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  handle_producer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_cu_func_list (struct dwarf2_cu*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * null_cleanup ; 
 int /*<<< orphan*/  process_die (struct die_info*,struct dwarf2_cu*) ; 
 int processing_gcc_compilation ; 
 int /*<<< orphan*/  record_debugformat (char*) ; 
 int /*<<< orphan*/  set_cu_language (unsigned int,struct dwarf2_cu*) ; 
 struct die_info* sibling_die (struct die_info*) ; 
 int /*<<< orphan*/  start_symtab (char*,char*,scalar_t__) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
read_file_scope (struct die_info *die, struct dwarf2_cu *cu)
{
  struct objfile *objfile = cu->objfile;
  struct comp_unit_head *cu_header = &cu->header;
  struct cleanup *back_to = make_cleanup (null_cleanup, 0);
  CORE_ADDR lowpc = ((CORE_ADDR) -1);
  CORE_ADDR highpc = ((CORE_ADDR) 0);
  struct attribute *attr;
  char *name = "<unknown>";
  char *comp_dir = NULL;
  struct die_info *child_die;
  bfd *abfd = objfile->obfd;
  struct line_header *line_header = 0;
  CORE_ADDR baseaddr;
  
  baseaddr = ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));

  get_scope_pc_bounds (die, &lowpc, &highpc, cu);

  /* If we didn't find a lowpc, set it to highpc to avoid complaints
     from finish_block.  */
  if (lowpc == ((CORE_ADDR) -1))
    lowpc = highpc;
  lowpc += baseaddr;
  highpc += baseaddr;

  attr = dwarf2_attr (die, DW_AT_name, cu);
  if (attr)
    {
      name = DW_STRING (attr);
    }
  attr = dwarf2_attr (die, DW_AT_comp_dir, cu);
  if (attr)
    {
      comp_dir = DW_STRING (attr);
      if (comp_dir)
	{
	  /* Irix 6.2 native cc prepends <machine>.: to the compilation
	     directory, get rid of it.  */
	  char *cp = strchr (comp_dir, ':');

	  if (cp && cp != comp_dir && cp[-1] == '.' && cp[1] == '/')
	    comp_dir = cp + 1;
	}
    }

  if (objfile->ei.entry_point >= lowpc &&
      objfile->ei.entry_point < highpc)
    {
      objfile->ei.deprecated_entry_file_lowpc = lowpc;
      objfile->ei.deprecated_entry_file_highpc = highpc;
    }

  attr = dwarf2_attr (die, DW_AT_language, cu);
  if (attr)
    {
      set_cu_language (DW_UNSND (attr), cu);
    }

  /* We assume that we're processing GCC output. */
  processing_gcc_compilation = 2;
#if 0
  /* FIXME:Do something here.  */
  if (dip->at_producer != NULL)
    {
      handle_producer (dip->at_producer);
    }
#endif

  /* The compilation unit may be in a different language or objfile,
     zero out all remembered fundamental types.  */
  memset (cu->ftypes, 0, FT_NUM_MEMBERS * sizeof (struct type *));

  start_symtab (name, comp_dir, lowpc);
  record_debugformat ("DWARF 2");

  initialize_cu_func_list (cu);

  /* Process all dies in compilation unit.  */
  if (die->child != NULL)
    {
      child_die = die->child;
      while (child_die && child_die->tag)
	{
	  process_die (child_die, cu);
	  child_die = sibling_die (child_die);
	}
    }

  /* Decode line number information if present.  */
  attr = dwarf2_attr (die, DW_AT_stmt_list, cu);
  if (attr)
    {
      unsigned int line_offset = DW_UNSND (attr);
      line_header = dwarf_decode_line_header (line_offset, abfd, cu);
      if (line_header)
        {
          make_cleanup ((make_cleanup_ftype *) free_line_header,
                        (void *) line_header);
          dwarf_decode_lines (line_header, comp_dir, abfd, cu);
        }
    }

  /* Decode macro information, if present.  Dwarf 2 macro information
     refers to information in the line number info statement program
     header, so we can only read it if we've read the header
     successfully.  */
  attr = dwarf2_attr (die, DW_AT_macro_info, cu);
  if (attr && line_header)
    {
      unsigned int macro_offset = DW_UNSND (attr);
      dwarf_decode_macros (line_header, macro_offset,
                           comp_dir, abfd, cu);
    }
  do_cleanups (back_to);
}