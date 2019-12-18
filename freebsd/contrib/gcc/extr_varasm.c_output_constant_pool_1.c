#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct constant_descriptor_rtx {int /*<<< orphan*/  mode; int /*<<< orphan*/  labelno; int /*<<< orphan*/  constant; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {TYPE_2__ common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* internal_label ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_SPECIAL_POOL_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  CONST 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 unsigned int GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_DELETED_P (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 128 
 int /*<<< orphan*/  NOTE_INSN_DELETED ; 
 int /*<<< orphan*/  NOTE_LINE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTE_P (int /*<<< orphan*/ ) ; 
 int PLUS ; 
 int SECTION_MERGE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_align (unsigned int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_4__* in_section ; 
 int /*<<< orphan*/  output_constant_pool_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ targetm ; 

__attribute__((used)) static void
output_constant_pool_1 (struct constant_descriptor_rtx *desc,
			unsigned int align)
{
  rtx x, tmp;

  x = desc->constant;

  /* See if X is a LABEL_REF (or a CONST referring to a LABEL_REF)
     whose CODE_LABEL has been deleted.  This can occur if a jump table
     is eliminated by optimization.  If so, write a constant of zero
     instead.  Note that this can also happen by turning the
     CODE_LABEL into a NOTE.  */
  /* ??? This seems completely and utterly wrong.  Certainly it's
     not true for NOTE_INSN_DELETED_LABEL, but I disbelieve proper
     functioning even with INSN_DELETED_P and friends.  */

  tmp = x;
  switch (GET_CODE (x))
    {
    case CONST:
      if (GET_CODE (XEXP (x, 0)) != PLUS
	  || GET_CODE (XEXP (XEXP (x, 0), 0)) != LABEL_REF)
	break;
      tmp = XEXP (XEXP (x, 0), 0);
      /* FALLTHRU  */

    case LABEL_REF:
      tmp = XEXP (x, 0);
      gcc_assert (!INSN_DELETED_P (tmp));
      gcc_assert (!NOTE_P (tmp)
		  || NOTE_LINE_NUMBER (tmp) != NOTE_INSN_DELETED);
      break;

    default:
      break;
    }

#ifdef ASM_OUTPUT_SPECIAL_POOL_ENTRY
  ASM_OUTPUT_SPECIAL_POOL_ENTRY (asm_out_file, x, desc->mode,
				 align, desc->labelno, done);
#endif

  assemble_align (align);

  /* Output the label.  */
  targetm.asm_out.internal_label (asm_out_file, "LC", desc->labelno);

  /* Output the data.  */
  output_constant_pool_2 (desc->mode, x, align);

  /* Make sure all constants in SECTION_MERGE and not SECTION_STRINGS
     sections have proper size.  */
  if (align > GET_MODE_BITSIZE (desc->mode)
      && in_section
      && (in_section->common.flags & SECTION_MERGE))
    assemble_align (align);

#ifdef ASM_OUTPUT_SPECIAL_POOL_ENTRY
 done:
#endif
  return;
}