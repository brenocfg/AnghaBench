#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_10__ {int /*<<< orphan*/  next_bb; } ;
struct TYPE_9__ {char const* hot_section_label; char const* cold_section_label; scalar_t__ function_frequency; int /*<<< orphan*/ * unlikely_text_section_name; int /*<<< orphan*/ * cold_section_end_label; int /*<<< orphan*/ * hot_section_end_label; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* begin_function ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* mark_decl_preserved ) (char const*) ;} ;
struct TYPE_7__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_DECLARE_FUNCTION_NAME (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASM_OUTPUT_FUNCTION_PREFIX (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ASM_OUTPUT_MAX_SKIP_ALIGN (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ BB_COLD_PARTITION ; 
 scalar_t__ BB_PARTITION (int /*<<< orphan*/ ) ; 
 int BITS_PER_UNIT ; 
 scalar_t__ CONSTANT_POOL_BEFORE_FUNCTION ; 
 int DECL_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_PRESERVE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_USER_ALIGN (int /*<<< orphan*/ ) ; 
 TYPE_5__* ENTRY_BLOCK_PTR ; 
 scalar_t__ FUNCTION_FREQUENCY_UNLIKELY_EXECUTED ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (scalar_t__) ; 
 scalar_t__ align_functions ; 
 int align_functions_log ; 
 int /*<<< orphan*/  app_disable () ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_align (int) ; 
 TYPE_4__* cfun ; 
 int /*<<< orphan*/  const_labelno ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  current_function_is_thunk ; 
 TYPE_3__* debug_hooks ; 
 int first_function_block_is_cold ; 
 int /*<<< orphan*/  flag_function_sections ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 
 int floor_log2 (int) ; 
 int /*<<< orphan*/  function_section (int /*<<< orphan*/ ) ; 
 void* ggc_strdup (char*) ; 
 int /*<<< orphan*/  globalize_decl (int /*<<< orphan*/ ) ; 
 int in_cold_section_p ; 
 int /*<<< orphan*/  initialize_cold_section_name () ; 
 int /*<<< orphan*/  maybe_assemble_visibility (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notice_global_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_constant_pool (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_unique_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char const*) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  text_section ; 
 int /*<<< orphan*/  unlikely_text_section () ; 

void
assemble_start_function (tree decl, const char *fnname)
{
  int align;
  char tmp_label[100];
  bool hot_label_written = false;

  cfun->unlikely_text_section_name = NULL;

  first_function_block_is_cold = false;
  if (flag_reorder_blocks_and_partition)
    {
      ASM_GENERATE_INTERNAL_LABEL (tmp_label, "LHOTB", const_labelno);
      cfun->hot_section_label = ggc_strdup (tmp_label);
      ASM_GENERATE_INTERNAL_LABEL (tmp_label, "LCOLDB", const_labelno);
      cfun->cold_section_label = ggc_strdup (tmp_label);
      ASM_GENERATE_INTERNAL_LABEL (tmp_label, "LHOTE", const_labelno);
      cfun->hot_section_end_label = ggc_strdup (tmp_label);
      ASM_GENERATE_INTERNAL_LABEL (tmp_label, "LCOLDE", const_labelno);
      cfun->cold_section_end_label = ggc_strdup (tmp_label);
      const_labelno++;
    }
  else
    {
      cfun->hot_section_label = NULL;
      cfun->cold_section_label = NULL;
      cfun->hot_section_end_label = NULL;
      cfun->cold_section_end_label = NULL;
    }

  /* The following code does not need preprocessing in the assembler.  */

  app_disable ();

  if (CONSTANT_POOL_BEFORE_FUNCTION)
    output_constant_pool (fnname, decl);

  resolve_unique_section (decl, 0, flag_function_sections);

  /* Make sure the not and cold text (code) sections are properly
     aligned.  This is necessary here in the case where the function
     has both hot and cold sections, because we don't want to re-set
     the alignment when the section switch happens mid-function.  */

  if (flag_reorder_blocks_and_partition)
    {
      switch_to_section (unlikely_text_section ());
      assemble_align (DECL_ALIGN (decl));
      ASM_OUTPUT_LABEL (asm_out_file, cfun->cold_section_label);

      /* When the function starts with a cold section, we need to explicitly
	 align the hot section and write out the hot section label.
	 But if the current function is a thunk, we do not have a CFG.  */
      if (!current_function_is_thunk
	  && BB_PARTITION (ENTRY_BLOCK_PTR->next_bb) == BB_COLD_PARTITION)
	{
	  switch_to_section (text_section);
	  assemble_align (DECL_ALIGN (decl));
	  ASM_OUTPUT_LABEL (asm_out_file, cfun->hot_section_label);
	  hot_label_written = true;
	  first_function_block_is_cold = true;
	}
    }
  else if (DECL_SECTION_NAME (decl))
    {
      /* Calls to function_section rely on first_function_block_is_cold
	 being accurate.  The first block may be cold even if we aren't
	 doing partitioning, if the entire function was decided by
	 choose_function_section (predict.c) to be cold.  */

      initialize_cold_section_name ();

      if (cfun->unlikely_text_section_name
	  && strcmp (TREE_STRING_POINTER (DECL_SECTION_NAME (decl)),
		     cfun->unlikely_text_section_name) == 0)
	first_function_block_is_cold = true;
    }

  in_cold_section_p = first_function_block_is_cold;

  /* Switch to the correct text section for the start of the function.  */

  switch_to_section (function_section (decl));
  if (flag_reorder_blocks_and_partition
      && !hot_label_written)
    ASM_OUTPUT_LABEL (asm_out_file, cfun->hot_section_label);

  /* Tell assembler to move to target machine's alignment for functions.  */
  align = floor_log2 (DECL_ALIGN (decl) / BITS_PER_UNIT);
  if (align > 0)
    {
      ASM_OUTPUT_ALIGN (asm_out_file, align);
    }

  /* Handle a user-specified function alignment.
     Note that we still need to align to DECL_ALIGN, as above,
     because ASM_OUTPUT_MAX_SKIP_ALIGN might not do any alignment at all.  */
  if (! DECL_USER_ALIGN (decl)
      && align_functions_log > align
      && cfun->function_frequency != FUNCTION_FREQUENCY_UNLIKELY_EXECUTED)
    {
#ifdef ASM_OUTPUT_MAX_SKIP_ALIGN
      ASM_OUTPUT_MAX_SKIP_ALIGN (asm_out_file,
				 align_functions_log, align_functions - 1);
#else
      ASM_OUTPUT_ALIGN (asm_out_file, align_functions_log);
#endif
    }

#ifdef ASM_OUTPUT_FUNCTION_PREFIX
  ASM_OUTPUT_FUNCTION_PREFIX (asm_out_file, fnname);
#endif

  (*debug_hooks->begin_function) (decl);

  /* Make function name accessible from other files, if appropriate.  */

  if (TREE_PUBLIC (decl))
    {
      notice_global_symbol (decl);

      globalize_decl (decl);

      maybe_assemble_visibility (decl);
    }

  if (DECL_PRESERVE_P (decl))
    targetm.asm_out.mark_decl_preserved (fnname);

  /* Do any machine/system dependent processing of the function name.  */
#ifdef ASM_DECLARE_FUNCTION_NAME
  ASM_DECLARE_FUNCTION_NAME (asm_out_file, fnname, current_function_decl);
#else
  /* Standard thing is just output label for the function.  */
  ASM_OUTPUT_LABEL (asm_out_file, fnname);
#endif /* ASM_DECLARE_FUNCTION_NAME */
}