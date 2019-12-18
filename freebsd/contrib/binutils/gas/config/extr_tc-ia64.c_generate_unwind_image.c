#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unw_rec_list ;
typedef  int /*<<< orphan*/  segT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_5__ {scalar_t__ X_add_symbol; scalar_t__ X_add_number; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
struct TYPE_7__ {int pointer_size; int flags; int /*<<< orphan*/  pointer_size_shift; } ;
struct TYPE_6__ {scalar_t__ personality_routine; int /*<<< orphan*/ * current_entry; int /*<<< orphan*/  tail; int /*<<< orphan*/  list; int /*<<< orphan*/  info; scalar_t__ force_unwind_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_IA64_LTOFF_FPTR32LSB ; 
 int /*<<< orphan*/  BFD_RELOC_IA64_LTOFF_FPTR32MSB ; 
 int /*<<< orphan*/  BFD_RELOC_IA64_LTOFF_FPTR64LSB ; 
 int /*<<< orphan*/  BFD_RELOC_IA64_LTOFF_FPTR64MSB ; 
 int EF_IA_64_ABI64 ; 
 int EF_IA_64_BE ; 
 int /*<<< orphan*/  NOT_A_CHAR ; 
 int /*<<< orphan*/  O_symbol ; 
 int /*<<< orphan*/  SPECIAL_SECTION_UNWIND_INFO ; 
 int /*<<< orphan*/  add_unwind_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int calc_record_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_build_dot () ; 
 int /*<<< orphan*/  fix_new_exp (int /*<<< orphan*/ ,scalar_t__,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_unw_records (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  frag_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 scalar_t__ frag_now_fix () ; 
 int /*<<< orphan*/  frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_saved_prologue_counts () ; 
 int /*<<< orphan*/  ia64_flush_insns () ; 
 TYPE_3__ md ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/ * optimize_unw_records (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_endp () ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_machine_dependent ; 
 int /*<<< orphan*/  start_unwind_section (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_2__ unwind ; 

__attribute__((used)) static void
generate_unwind_image (const segT text_seg)
{
  int size, pad;
  unw_rec_list *list;

  /* Mark the end of the unwind info, so that we can compute the size of the
     last unwind region.  */
  add_unwind_entry (output_endp (), NOT_A_CHAR);

  /* Force out pending instructions, to make sure all unwind records have
     a valid slot_number field.  */
  ia64_flush_insns ();

  /* Generate the unwind record.  */
  list = optimize_unw_records (unwind.list);
  fixup_unw_records (list, 1);
  size = calc_record_size (list);

  if (size > 0 || unwind.force_unwind_entry)
    {
      unwind.force_unwind_entry = 0;
      /* pad to pointer-size boundary.  */
      pad = size % md.pointer_size;
      if (pad != 0)
	size += md.pointer_size - pad;
      /* Add 8 for the header.  */
      size += 8;
      /* Add a pointer for the personality offset.  */
      if (unwind.personality_routine)
	size += md.pointer_size;
    }

  /* If there are unwind records, switch sections, and output the info.  */
  if (size != 0)
    {
      expressionS exp;
      bfd_reloc_code_real_type reloc;

      start_unwind_section (text_seg, SPECIAL_SECTION_UNWIND_INFO);

      /* Make sure the section has 4 byte alignment for ILP32 and
	 8 byte alignment for LP64.  */
      frag_align (md.pointer_size_shift, 0, 0);
      record_alignment (now_seg, md.pointer_size_shift);

      /* Set expression which points to start of unwind descriptor area.  */
      unwind.info = expr_build_dot ();
      
      frag_var (rs_machine_dependent, size, size, 0, 0,
		(offsetT) (long) unwind.personality_routine,
		(char *) list);

      /* Add the personality address to the image.  */
      if (unwind.personality_routine != 0)
	{
	  exp.X_op = O_symbol;
	  exp.X_add_symbol = unwind.personality_routine;
	  exp.X_add_number = 0;

	  if (md.flags & EF_IA_64_BE)
	    {
	      if (md.flags & EF_IA_64_ABI64)
		reloc = BFD_RELOC_IA64_LTOFF_FPTR64MSB;
	      else
		reloc = BFD_RELOC_IA64_LTOFF_FPTR32MSB;
	    }
	  else
	    {
	      if (md.flags & EF_IA_64_ABI64)
		reloc = BFD_RELOC_IA64_LTOFF_FPTR64LSB;
	      else
		reloc = BFD_RELOC_IA64_LTOFF_FPTR32LSB;
	    }

	  fix_new_exp (frag_now, frag_now_fix () - md.pointer_size,
		       md.pointer_size, &exp, 0, reloc);
	  unwind.personality_routine = 0;
	}
    }

  free_saved_prologue_counts ();
  unwind.list = unwind.tail = unwind.current_entry = NULL;
}