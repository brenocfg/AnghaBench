#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ entry_point; scalar_t__ entry_func_highpc; scalar_t__ entry_func_lowpc; } ;
struct objfile {TYPE_1__ ei; int /*<<< orphan*/  section_offsets; } ;
struct dwarf2_cu {scalar_t__ language; int /*<<< orphan*/ * list_in_scope; struct objfile* objfile; } ;
struct die_info {scalar_t__ tag; struct die_info* child; int /*<<< orphan*/  type; } ;
struct context_stack {int /*<<< orphan*/  params; int /*<<< orphan*/  locals; int /*<<< orphan*/  old_blocks; int /*<<< orphan*/  name; } ;
struct cleanup {int dummy; } ;
struct attribute {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_AT_frame_base ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  add_to_cu_func_list (char*,scalar_t__,scalar_t__,struct dwarf2_cu*) ; 
 char* determine_prefix (struct die_info*,struct dwarf2_cu*) ; 
 struct die_info* die_specification (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct attribute* dwarf2_attr (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf2_get_pc_bounds (struct die_info*,scalar_t__*,scalar_t__*,struct dwarf2_cu*) ; 
 char* dwarf2_linkage_name (struct die_info*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  dwarf2_symbol_mark_computed (struct attribute*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  file_symbols ; 
 int /*<<< orphan*/  finish_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct objfile*) ; 
 scalar_t__ language_cplus ; 
 int /*<<< orphan*/  local_symbols ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  new_symbol (struct die_info*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 
 scalar_t__ outermost_context_p () ; 
 int /*<<< orphan*/  param_symbols ; 
 struct context_stack* pop_context () ; 
 int /*<<< orphan*/  process_die (struct die_info*,struct dwarf2_cu*) ; 
 char const* processing_current_prefix ; 
 struct context_stack* push_context (int /*<<< orphan*/ ,scalar_t__) ; 
 struct die_info* sibling_die (struct die_info*) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
read_func_scope (struct die_info *die, struct dwarf2_cu *cu)
{
  struct objfile *objfile = cu->objfile;
  struct context_stack *new;
  CORE_ADDR lowpc;
  CORE_ADDR highpc;
  struct die_info *child_die;
  struct attribute *attr;
  char *name;
  const char *previous_prefix = processing_current_prefix;
  struct cleanup *back_to = NULL;
  CORE_ADDR baseaddr;

  baseaddr = ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));

  name = dwarf2_linkage_name (die, cu);

  /* Ignore functions with missing or empty names and functions with
     missing or invalid low and high pc attributes.  */
  if (name == NULL || !dwarf2_get_pc_bounds (die, &lowpc, &highpc, cu))
    return;

  if (cu->language == language_cplus)
    {
      struct die_info *spec_die = die_specification (die, cu);

      /* NOTE: carlton/2004-01-23: We have to be careful in the
         presence of DW_AT_specification.  For example, with GCC 3.4,
         given the code

           namespace N {
             void foo() {
               // Definition of N::foo.
             }
           }

         then we'll have a tree of DIEs like this:

         1: DW_TAG_compile_unit
           2: DW_TAG_namespace        // N
             3: DW_TAG_subprogram     // declaration of N::foo
           4: DW_TAG_subprogram       // definition of N::foo
                DW_AT_specification   // refers to die #3

         Thus, when processing die #4, we have to pretend that we're
         in the context of its DW_AT_specification, namely the contex
         of die #3.  */
	
      if (spec_die != NULL)
	{
	  char *specification_prefix = determine_prefix (spec_die, cu);
	  processing_current_prefix = specification_prefix;
	  back_to = make_cleanup (xfree, specification_prefix);
	}
    }

  lowpc += baseaddr;
  highpc += baseaddr;

  /* Record the function range for dwarf_decode_lines.  */
  add_to_cu_func_list (name, lowpc, highpc, cu);

  if (objfile->ei.entry_point >= lowpc &&
      objfile->ei.entry_point < highpc)
    {
      objfile->ei.entry_func_lowpc = lowpc;
      objfile->ei.entry_func_highpc = highpc;
    }

  new = push_context (0, lowpc);
  new->name = new_symbol (die, die->type, cu);

  /* If there is a location expression for DW_AT_frame_base, record
     it.  */
  attr = dwarf2_attr (die, DW_AT_frame_base, cu);
  if (attr)
    /* FIXME: cagney/2004-01-26: The DW_AT_frame_base's location
       expression is being recorded directly in the function's symbol
       and not in a separate frame-base object.  I guess this hack is
       to avoid adding some sort of frame-base adjunct/annex to the
       function's symbol :-(.  The problem with doing this is that it
       results in a function symbol with a location expression that
       has nothing to do with the location of the function, ouch!  The
       relationship should be: a function's symbol has-a frame base; a
       frame-base has-a location expression.  */
    dwarf2_symbol_mark_computed (attr, new->name, cu);

  cu->list_in_scope = &local_symbols;

  if (die->child != NULL)
    {
      child_die = die->child;
      while (child_die && child_die->tag)
	{
	  process_die (child_die, cu);
	  child_die = sibling_die (child_die);
	}
    }

  new = pop_context ();
  /* Make a block for the local symbols within.  */
  finish_block (new->name, &local_symbols, new->old_blocks,
		lowpc, highpc, objfile);
  
  /* In C++, we can have functions nested inside functions (e.g., when
     a function declares a class that has methods).  This means that
     when we finish processing a function scope, we may need to go
     back to building a containing block's symbol lists.  */
  local_symbols = new->locals;
  param_symbols = new->params;

  /* If we've finished processing a top-level function, subsequent
     symbols go in the file symbol list.  */
  if (outermost_context_p ())
    cu->list_in_scope = &file_symbols;

  processing_current_prefix = previous_prefix;
  if (back_to != NULL)
    do_cleanups (back_to);
}