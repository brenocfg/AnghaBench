#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int offsetT ;
struct TYPE_12__ {char* fr_literal; int fr_fix; struct TYPE_12__* fr_next; } ;
typedef  TYPE_3__ fragS ;
typedef  enum bfd_reloc_code_real { ____Placeholder_bfd_reloc_code_real } bfd_reloc_code_real ;
struct TYPE_15__ {scalar_t__ X_op; scalar_t__ X_add_symbol; int /*<<< orphan*/  X_add_number; int /*<<< orphan*/  X_op_symbol; } ;
struct TYPE_10__ {int opcode_modifier; } ;
struct TYPE_14__ {unsigned int operands; int* types; scalar_t__ suffix; TYPE_2__* op; int /*<<< orphan*/ * reloc; TYPE_1__ tm; } ;
struct TYPE_13__ {scalar_t__ X_op; } ;
struct TYPE_11__ {TYPE_9__* imms; } ;

/* Variables and functions */
 int BFD_RELOC_32 ; 
 int BFD_RELOC_386_GOTPC ; 
 int BFD_RELOC_64 ; 
 int BFD_RELOC_X86_64_32S ; 
 int BFD_RELOC_X86_64_GOTPC32 ; 
 int BFD_RELOC_X86_64_GOTPC64 ; 
 scalar_t__ GOT_symbol ; 
 int Imm ; 
 int Imm32S ; 
 int No_lSuf ; 
 scalar_t__ O_add ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_subtract ; 
 scalar_t__ O_symbol ; 
 scalar_t__ QWORD_MNEM_SUFFIX ; 
 int /*<<< orphan*/  fix_new_exp (TYPE_3__*,int,int,TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 char* frag_more (int) ; 
 TYPE_3__* frag_now ; 
 TYPE_6__ i ; 
 int imm_size (unsigned int) ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int,int) ; 
 int /*<<< orphan*/  object_64bit ; 
 int offset_in_range (int /*<<< orphan*/ ,int) ; 
 int reloc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* symbol_get_value_expression (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_imm (fragS *insn_start_frag, offsetT insn_start_off)
{
  char *p;
  unsigned int n;

  for (n = 0; n < i.operands; n++)
    {
      if (i.types[n] & Imm)
	{
	  if (i.op[n].imms->X_op == O_constant)
	    {
	      int size = imm_size (n);
	      offsetT val;

	      val = offset_in_range (i.op[n].imms->X_add_number,
				     size);
	      p = frag_more (size);
	      md_number_to_chars (p, val, size);
	    }
	  else
	    {
	      /* Not absolute_section.
		 Need a 32-bit fixup (don't support 8bit
		 non-absolute imms).  Try to support other
		 sizes ...  */
	      enum bfd_reloc_code_real reloc_type;
	      int size = imm_size (n);
	      int sign;

	      if ((i.types[n] & (Imm32S))
		  && (i.suffix == QWORD_MNEM_SUFFIX
		      || (!i.suffix && (i.tm.opcode_modifier & No_lSuf))))
		sign = 1;
	      else
		sign = 0;

	      p = frag_more (size);
	      reloc_type = reloc (size, 0, sign, i.reloc[n]);

	      /*   This is tough to explain.  We end up with this one if we
	       * have operands that look like
	       * "_GLOBAL_OFFSET_TABLE_+[.-.L284]".  The goal here is to
	       * obtain the absolute address of the GOT, and it is strongly
	       * preferable from a performance point of view to avoid using
	       * a runtime relocation for this.  The actual sequence of
	       * instructions often look something like:
	       *
	       *	call	.L66
	       * .L66:
	       *	popl	%ebx
	       *	addl	$_GLOBAL_OFFSET_TABLE_+[.-.L66],%ebx
	       *
	       *   The call and pop essentially return the absolute address
	       * of the label .L66 and store it in %ebx.  The linker itself
	       * will ultimately change the first operand of the addl so
	       * that %ebx points to the GOT, but to keep things simple, the
	       * .o file must have this operand set so that it generates not
	       * the absolute address of .L66, but the absolute address of
	       * itself.  This allows the linker itself simply treat a GOTPC
	       * relocation as asking for a pcrel offset to the GOT to be
	       * added in, and the addend of the relocation is stored in the
	       * operand field for the instruction itself.
	       *
	       *   Our job here is to fix the operand so that it would add
	       * the correct offset so that %ebx would point to itself.  The
	       * thing that is tricky is that .-.L66 will point to the
	       * beginning of the instruction, so we need to further modify
	       * the operand so that it will point to itself.  There are
	       * other cases where you have something like:
	       *
	       *	.long	$_GLOBAL_OFFSET_TABLE_+[.-.L66]
	       *
	       * and here no correction would be required.  Internally in
	       * the assembler we treat operands of this form as not being
	       * pcrel since the '.' is explicitly mentioned, and I wonder
	       * whether it would simplify matters to do it this way.  Who
	       * knows.  In earlier versions of the PIC patches, the
	       * pcrel_adjust field was used to store the correction, but
	       * since the expression is not pcrel, I felt it would be
	       * confusing to do it this way.  */

	      if ((reloc_type == BFD_RELOC_32
		   || reloc_type == BFD_RELOC_X86_64_32S
		   || reloc_type == BFD_RELOC_64)
		  && GOT_symbol
		  && GOT_symbol == i.op[n].imms->X_add_symbol
		  && (i.op[n].imms->X_op == O_symbol
		      || (i.op[n].imms->X_op == O_add
			  && ((symbol_get_value_expression
			       (i.op[n].imms->X_op_symbol)->X_op)
			      == O_subtract))))
		{
		  offsetT add;

		  if (insn_start_frag == frag_now)
		    add = (p - frag_now->fr_literal) - insn_start_off;
		  else
		    {
		      fragS *fr;

		      add = insn_start_frag->fr_fix - insn_start_off;
		      for (fr = insn_start_frag->fr_next;
			   fr && fr != frag_now; fr = fr->fr_next)
			add += fr->fr_fix;
		      add += p - frag_now->fr_literal;
		    }

		  if (!object_64bit)
		    reloc_type = BFD_RELOC_386_GOTPC;
		  else if (size == 4)
		    reloc_type = BFD_RELOC_X86_64_GOTPC32;
		  else if (size == 8)
		    reloc_type = BFD_RELOC_X86_64_GOTPC64;
		  i.op[n].imms->X_add_number += add;
		}
	      fix_new_exp (frag_now, p - frag_now->fr_literal, size,
			   i.op[n].imms, 0, reloc_type);
	    }
	}
    }
}