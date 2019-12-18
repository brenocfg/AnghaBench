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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  LABEL_REF_NONLOCAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_LABEL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_for_label_ref (rtx *rtl, void *data)
{
  rtx insn = (rtx) data;

  /* If this insn uses a LABEL_REF and there isn't a REG_LABEL note for it,
     we must rerun jump since it needs to place the note.  If this is a
     LABEL_REF for a CODE_LABEL that isn't in the insn chain, don't do this
     since no REG_LABEL will be added.  */
  return (GET_CODE (*rtl) == LABEL_REF
	  && ! LABEL_REF_NONLOCAL_P (*rtl)
	  && LABEL_P (XEXP (*rtl, 0))
	  && INSN_UID (XEXP (*rtl, 0)) != 0
	  && ! find_reg_note (insn, REG_LABEL, XEXP (*rtl, 0)));
}